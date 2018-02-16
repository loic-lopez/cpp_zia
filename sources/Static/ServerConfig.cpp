//
// Created by loic lopez on 23/01/2018.
//

#include <experimental/filesystem>
#include <Static/ServerConfig.hpp>

namespace fs = std::experimental::filesystem;
namespace Json = nlohmann;

std::map<ServerCoreId, zia::api::ConfObject> ServerConfig::WebSiteConfs;
zia::api::ConfObject ServerConfig::ServerConf;

template<typename T>
static inline zia::api::ConfValue CreateConfValueFromType(T type)
{
    zia::api::ConfValue confValue;
    confValue.v = type;
    return confValue;
}

static inline bool fileEndsWith(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

inline void ServerConfig::DefaultConfig()
{
    (void) static_constructor<&ServerConfig::DefaultConfig>::c;
    ServerCoreId serverCoreId = 0;

    ServerConfig::LoadDefaultServerConfig();
    std::string websitesPath = std::get<std::string>(ServerConf["websites_conf_dir"].v);

    if (fs::exists(fs::path(websitesPath.c_str())))
        for (const auto &name : scandirpp::get_names(websitesPath))
        {
            if (fileEndsWith(name, ".json"))
                WebSiteConfs[serverCoreId++] = LoadConfigFromFile(websitesPath.append("/") + name);
        }

    if (WebSiteConfs.empty())
    {
        ServerConfig::LoadDefaultWebSiteConf();
    }
}

bool ServerConfig::isConfigFileExists(const std::string &path)
{
    return fs::exists(fs::path(path.c_str()));
}

void  ServerConfig::FormatIPAddress(sockaddr_in &addr, int port, std::string host)
{

    hostent *record = gethostbyname(host.c_str());
    if(record == nullptr)
        return;

    memcpy(&addr.sin_addr, record->h_addr_list[0], record->h_length);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
}

inline zia::api::ConfObject ServerConfig::LoadConfigFromFile(const std::string &path)
{
    Json::json json;
    std::ifstream configFile(fs::path(path.c_str()));
    zia::api::ConfObject confObject;

    configFile >> json;
    for (Json::json::iterator it = json.begin(); it != json.end(); ++it)
    {
        std::string value = it.value();
        std::string key = it.key();
        zia::api::ConfValue confValue;
        if (key == "port")
            confValue = CreateConfValueFromType(std::stoll(value));
        else
            confValue = CreateConfValueFromType(value);
        confObject[key] = confValue;
    }

    std::vector<std::string> requiredKeys = {"document_root", "server_name", "port"};

    for (const auto &requiredKey : requiredKeys)
    {
        if (confObject.find(requiredKey) == confObject.end())
            throw std::runtime_error("configuration required : " + requiredKey + " in : " + path);
    }
    return confObject;
}

inline void ServerConfig::LoadDefaultServerConfig()
{
    if (isConfigFileExists("config/server.conf.json"))
    {
        Json::json json;
        std::ifstream configFile(fs::path("config/server.conf.json"));

        configFile >> json;
        for (Json::json::iterator it = json.begin(); it != json.end(); ++it)
        {
            std::string value = it.value();
            std::string key = it.key();

            ServerConf[key] = CreateConfValueFromType(value);
        }
    }
    else
    {
        ServerConf["websites_conf_dir"] = CreateConfValueFromType(std::string("config/websites.conf.json.d"));
    }
}

inline void ServerConfig::LoadDefaultWebSiteConf()
{
    WebSiteConfs[0] = []() -> zia::api::ConfObject
    {
        zia::api::ConfObject confObject;

        confObject["port"] = CreateConfValueFromType(static_cast<long long>(8080));
        confObject["document_root"] = CreateConfValueFromType(std::string("html/"));
        confObject["server_name"] = CreateConfValueFromType(std::string("localhost"));
        return confObject;
    }();
}