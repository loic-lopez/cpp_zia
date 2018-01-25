//
// Created by loic lopez on 25/01/2018.
//

#include <Core/ServerLauncher.hpp>

ServerLauncher ServerLauncher::m_instance = ServerLauncher();


ServerLauncher &ServerLauncher::Instance()
{
    return m_instance;
}

ServerLauncher::ServerLauncher()
{

}

ServerLauncher::~ServerLauncher()
{

}


void ServerLauncher::launch()
{

    for (const auto &conf : ServerConfig::WebSiteConfs)
    {
        zia::api::Net *server = new ServerCore(conf.first, conf.second,
                                               [&server](zia::api::Net::Raw rawData, zia::api::NetInfo netInfo)
                                               {
                                                   ServerCore *serverCore = reinterpret_cast<ServerCore *>(server);
                                                   serverCore->getThreadPool().addThread(std::move(rawData),
                                                                                         std::move(netInfo));
                                               });
        this->servers[conf.first] = std::shared_ptr<zia::api::Net>(server);
    }

    while (true);
}