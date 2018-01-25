//
// Created by loic lopez on 23/01/2018.
//

#ifndef CPP_ZIA_CONFIG_HPP
#define CPP_ZIA_CONFIG_HPP

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <string>
#include <Library/json.hpp>
#include "static_constructor.hpp"
#include "api/conf.h"

class ServerConfig
{
private:
    static void DefaultConfig();
public:

    static zia::api::ConfValue ServerPort;
    static zia::api::ConfValue ServerIP;
    static zia::api::ConfValue ConfigPath;
    static zia::api::ConfValue DocumentWebRootPath;
    static bool LoadConfigFromFile();

    static bool isConfigFileExists();
    static struct sockaddr FormatIPAdress(struct sockaddr_in &addr);

};


#endif //CPP_ZIA_CONFIG_HPP
