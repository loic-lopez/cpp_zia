//
// Created by loic lopez on 23/01/2018.
//

#include <fstream>
#include <Static/ServerConfig.hpp>

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

    return false;
}

bool ServerConfig::isConfigFileExistant(const std::string &file)
{
    std::ifstream f(file.c_str());  // New enough C++ library will accept just name
    if (f.is_open())
    {
        f.close();
        return true;
    }
    else
        return false;
}

