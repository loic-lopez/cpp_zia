//
// Created by loic lopez on 23/01/2018.
//

#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>
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

    ServerIP.v = "127.0.0.1";
    ServerPort.v = static_cast<long long>(80);
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
    }

    std::cout << std::get<std::string>(DocumentWebRootPath.v) << std::endl;
    std::cout << std::get<long long>(ServerPort.v) << std::endl;
    return false;
}

bool ServerConfig::isConfigFileExists()
{
    return fs::exists(fs::path(std::get<std::string>(ConfigPath.v)));
}

