//
// Created by loic lopez on 23/01/2018.
//

#ifndef CPP_ZIA_CONFIG_HPP
#define CPP_ZIA_CONFIG_HPP

#ifdef WIN32

#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>

#else
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif
#include <fstream>
#include <iostream>
#include <string>
#include <Library/json.hpp>
#include <Library/ScanDir.hpp>
#include "static_constructor.hpp"
#include "api/conf.h"

using ServerCoreId = int;

class ServerConfig
{
private:
    static void DefaultConfig();
    static void LoadDefaultServerConfig();
    static zia::api::ConfObject LoadConfigFromFile(const std::string &);
    static bool isConfigFileExists(const std::string &path);

public:
    static std::map<ServerCoreId, zia::api::ConfObject> WebSiteConfs;
    static zia::api::ConfObject ServerConf;
    static zia::api::ConfValue ServerPort;
    static zia::api::ConfValue ServerIP;
    static zia::api::ConfValue ConfigPath;

    static zia::api::ConfValue DocumentWebRootPath;
    static struct sockaddr FormatIPAdress(struct sockaddr_in &addr);

};


#endif //CPP_ZIA_CONFIG_HPP
