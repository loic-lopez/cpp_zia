//
// Created by loic lopez on 23/01/2018.
//

#ifndef CPP_ZIA_CONFIG_HPP
#define CPP_ZIA_CONFIG_HPP

#include <string>
#include <Library/json.hpp>
#include "static_constructor.hpp"

class ServerConfig
{
private:
    static void DefaultConfig();

public:
    static unsigned int ServerPort;
    static std::string  ServerIP;

    static bool LoadConfigFromFile(const std::string &file);
    static bool isConfigFileExists(const std::string &file);

};


#endif //CPP_ZIA_CONFIG_HPP
