#include <Thread/HttpHandler.hpp>
#include <Static/ServerConfig.hpp>
#include <iostream>

int main()
{

    //HttpHandler httpHandler;
    if (ServerConfig::isConfigFileExists("toto"))
        std::cout << "found" << std::endl;
    else
        std::cout << "not found" << std::endl;

    return 0;
}