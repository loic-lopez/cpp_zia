//
// Created by loic lopez on 25/01/2018.
//

#ifndef CPP_ZIA_SERVERLAUNCHER_HPP
#define CPP_ZIA_SERVERLAUNCHER_HPP

#include "ServerCore.hpp"

class ServerLauncher
{
private:
    std::map<unsigned int, std::shared_ptr<zia::api::Net>> servers;

    ServerLauncher& operator= (const ServerLauncher&){}
    ServerLauncher (const ServerLauncher&){}

    static ServerLauncher m_instance;
    ServerLauncher();
    ~ServerLauncher();

public:
    void launch();
    static ServerLauncher& Instance();
};


#endif //CPP_ZIA_SERVERLAUNCHER_HPP
