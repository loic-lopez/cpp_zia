//
// Created by loic lopez on 23/01/2018.
//

#include <experimental/filesystem>
#include <Static/ServerConfig.hpp>

namespace fs = std::experimental::filesystem;
namespace Json = nlohmann;

zia::api::ConfValue ServerConfig::ServerIP;
zia::api::ConfValue ServerConfig::ServerPort;

inline void ServerConfig::DefaultConfig()
{
    (void) static_constructor<&ServerConfig::DefaultConfig>::c;

    ServerIP.v = "127.0.0.1";
    ServerPort.v = 80;
}

bool ServerConfig::LoadConfigFromFile(const std::string &file)
{
    Json::json j;

    return false;
}

bool ServerConfig::isConfigFileExists(const std::string &file)
{
    return fs::exists(fs::path(file.c_str()));
}

