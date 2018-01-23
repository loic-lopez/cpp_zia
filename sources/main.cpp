#include <Thread/HttpHandler.hpp>
#include <Static/ServerConfig.hpp>
#include <iostream>
#include "api/conf.h"

int main()
{

    //HttpHandler httpHandler;
    if (ServerConfig::isConfigFileExistant("toto"))
        std::cout << "found" << std::endl;
    else
        std::cout << "not found" << std::endl;

    return 0;
}