//
// Created by loic lopez on 23/01/2018.
//

#include <experimental/filesystem>
#include <Static/ServerConfig.hpp>
#include <iostream>

namespace fs = std::experimental::filesystem;
namespace Json = nlohmann;

zia::api::ConfValue ServerConfig::ServerIP;
zia::api::ConfValue ServerConfig::ServerPort;
zia::api::ConfValue ServerConfig::ConfigPath;

inline void ServerConfig::DefaultConfig()
{
    (void) static_constructor<&ServerConfig::DefaultConfig>::c;

    ServerIP.v = "127.0.0.1";
    ServerPort.v = static_cast<long long>(80);
    ConfigPath.v = std::string("config/zia.conf.json");
}

bool ServerConfig::LoadConfigFromFile()
{
    Json::json j;

    return false;
}

bool ServerConfig::isConfigFileExists()
{
    return fs::exists(fs::path(std::get<std::string>(ConfigPath.v)));
}

