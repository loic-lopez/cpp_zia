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

inline void ServerConfig::DefaultConfig()
{
    (void) static_constructor<&ServerConfig::DefaultConfig>::c;

    ServerIP.v = std::string("127.0.0.1");
    ServerPort.v = static_cast<long long>(8080);
    ConfigPath.v = std::string("config/zia.conf.json");
    DocumentWebRootPath.v = std::string("html/");
}

bool ServerConfig::LoadConfigFromFile()
{
    Json::json json;
    std::ifstream configFile(fs::path(std::get<std::string>(ConfigPath.v)));

    configFile >> json;

    for (Json::json::iterator it = json.begin(); it != json.end(); ++it)
    {
        if (it.key() == "root")
            DocumentWebRootPath.v = std::string(it.value());
        else if (it.key() == "port")
            ServerPort.v = std::atoll(std::string(it.value()).c_str());
        else if (it.key() == "server_name")
            ServerIP.v = std::string(it.value());
    }

    std::cout << std::get<std::string>(DocumentWebRootPath.v) << std::endl;
    std::cout << std::get<std::string>(ServerIP.v) << std::endl;
    std::cout << std::get<long long>(ServerPort.v) << std::endl;
    return false;
}

bool ServerConfig::isConfigFileExists()
{
    return fs::exists(fs::path(std::get<std::string>(ConfigPath.v)));
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