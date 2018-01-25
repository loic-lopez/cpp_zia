//
// Created by loic lopez on 23/01/2018.
//

#include <experimental/filesystem>
#include <Static/ServerConfig.hpp>

namespace fs = std::experimental::filesystem;
namespace Json = nlohmann;

zia::api::ConfValue ServerConfig::ServerIP;
zia::api::ConfValue ServerConfig::ServerPort;
zia::api::ConfValue ServerConfig::ConfigPath;
zia::api::ConfValue ServerConfig::DocumentWebRootPath;
std::map<ServerCoreId, zia::api::ConfObject> ServerConfig::WebSiteConfs;
zia::api::ConfObject ServerConfig::ServerConf;

template<typename T>
static inline zia::api::ConfValue CreateConfValueFromType(T type)
{
    zia::api::ConfValue confValue;
    confValue.v = type;
    return confValue;
}

static inline bool fileEndsWith(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
}

inline void ServerConfig::DefaultConfig()
{
    (void) static_constructor<&ServerConfig::DefaultConfig>::c;
    ServerCoreId  serverCoreId = 0;
    LoadDefaultServerConfig();

    std::string websitesPath = std::get<std::string>(ServerConf["websites_conf_dir"].v);

    for (const auto& name : scandirpp::get_names(websitesPath))
    {
        if (fileEndsWith(name, ".json"))
            WebSiteConfs[serverCoreId++] = LoadConfigFromFile(websitesPath + '/' + name);
    }

    if (WebSiteConfs.empty())
    {
        WebSiteConfs[0] = [] () -> zia::api::ConfObject {
            zia::api::ConfObject confObject;

            confObject["port"] = CreateConfValueFromType(static_cast<long long>(8080));
            confObject["root"] = CreateConfValueFromType(std::string("/html"));
            confObject["server_name"] = CreateConfValueFromType(std::string("localhost"));
            return confObject;
        }();
    }

    ServerIP.v = std::string("127.0.0.1");
    ServerPort.v = static_cast<long long>(8080);
    ConfigPath.v = std::string("config/localhost.conf.json");
    DocumentWebRootPath.v = std::string("html/");
}

bool ServerConfig::isConfigFileExists(const std::string &path)
{
    return fs::exists(fs::path(path.c_str()));
}

struct sockaddr ServerConfig::FormatIPAdress(struct sockaddr_in &addr)
{
    struct sockaddr addrRet;
    struct hostent *lphost;
    u_long IP;
    std::string host = std::get<std::string>(ServerIP.v);
    int port = std::get<long long>(ServerPort.v);

    std::memset((char *) &addr, 0, sizeof(addr));
    if ((IP = inet_addr(host.c_str())) == (u_long) INADDR_NONE)
    {
        if ((lphost = gethostbyname(host.c_str())) == nullptr)
        {
            std::memset((char *) &addrRet, 0, sizeof(addrRet));
            return addrRet;
        }
        addr.sin_family = lphost->h_addrtype;
#ifdef _WIN16
        _fmemcpy (&addr.sin_addr, lphost->h_addr, lphost->h_length);
#else
        std::memcpy(&addr.sin_addr, lphost->h_addr, lphost->h_length);
#endif
    }
    else
    {
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = IP;
    }
    addr.sin_port = htons((u_short) port);

    std::memcpy((char *) &addrRet, (char *) &addr, sizeof(addrRet));
    return addrRet;
}

zia::api::ConfObject ServerConfig::LoadConfigFromFile(const std::string &path)
{
    Json::json json;
    std::ifstream configFile(fs::path(path.c_str()));
    zia::api::ConfObject confObject;

    configFile >> json;
    for (Json::json::iterator it = json.begin(); it != json.end(); ++it) {
        std::string value = it.value();
        std::string key = it.key();
        zia::api::ConfValue confValue;
        if (key == "port")
            confValue.v = std::stoll(value);
        else
            confValue.v = value;
        confObject[key] = confValue;
    }

    std::vector<std::string> requiredKeys = {"document_root", "server_name", "port"};

    for (const auto &requiredKey : requiredKeys)
    {
        if (confObject.find(requiredKey) == confObject.end())
            throw std::runtime_error("configuration required : " + requiredKey + " in : " + path);
    }

}

void ServerConfig::LoadDefaultServerConfig()
{
    if (isConfigFileExists("config/server.conf.json"))
    {
        Json::json json;
        std::ifstream configFile(fs::path("config/server.conf.json"));

        configFile >> json;
        for (Json::json::iterator it = json.begin(); it != json.end(); ++it) {
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
