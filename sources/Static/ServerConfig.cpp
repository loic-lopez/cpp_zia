//
// Created by loic lopez on 23/01/2018.
//

#include <Static/ServerConfig.hpp>

std::string ServerConfig::ServerIP;
unsigned int ServerConfig::ServerPort;

inline void ServerConfig::DefaultConfig()
{
    (void)static_constructor<&ServerConfig::DefaultConfig>::c;

    ServerIP = "127.0.0.1";
    ServerPort = 80;
}

inline bool ServerConfig::LoadConfigFromFile(const std::string &file)
{

    return false;
}

inline bool ServerConfig::isConfigFileExistant(const std::string &file)
{
}

