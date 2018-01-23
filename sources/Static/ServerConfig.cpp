//
// Created by loic lopez on 23/01/2018.
//

#include <experimental/filesystem>
#include <Static/ServerConfig.hpp>

namespace fs = std::experimental::filesystem;
namespace Json = nlohmann;

std::string ServerConfig::ServerIP;
unsigned int ServerConfig::ServerPort;

inline void ServerConfig::DefaultConfig()
{
    (void) static_constructor<&ServerConfig::DefaultConfig>::c;

    ServerIP = "127.0.0.1";
    ServerPort = 80;
}

bool ServerConfig::LoadConfigFromFile(const std::string &file)
{
    Json::json j;

    j.lo

    return false;
}

bool ServerConfig::isConfigFileExistant(const std::string &file)
{
    return fs::exists(fs::path(file.c_str()));
}

