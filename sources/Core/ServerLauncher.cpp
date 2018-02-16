//
// Created by loic lopez on 25/01/2018.
//

#include <Core/ServerLauncher.hpp>

ServerLauncher ServerLauncher::m_instance = ServerLauncher();


ServerLauncher &ServerLauncher::Instance()
{
    return m_instance;
}

#ifdef _WIN32
ServerLauncher::ServerLauncher()
#else
ServerLauncher::ServerLauncher() : SignalHandler()
#endif
{

}

ServerLauncher::~ServerLauncher()
{

}


void ServerLauncher::launch()
{
    std::cout << "SIG";
    for (const auto &conf : ServerConfig::WebSiteConfs)
    {
        zia::api::Net *server = new ServerCore(conf.first, conf.second, [&server](zia::api::Net::Raw rawData, zia::api::NetInfo netInfo)
        {
            auto serverCore = reinterpret_cast<ServerCore *>(server);
            HttpHandler httpHandler = HttpHandler(rawData, netInfo, serverCore->getDocumentRootPath(), serverCore->getServerCoreId());
            serverCore->getThreadPool().doJob(std::bind(&HttpHandler::run, httpHandler));
        });
        this->servers[conf.first] = std::shared_ptr<zia::api::Net>(server);
    }

    while (!servers.empty());
}

zia::api::Net *ServerLauncher::getServer(ServerCoreId serverCoreId)
{
    return this->servers.at(serverCoreId).get();
}

bool ServerLauncher::handleSignal(int signal)
{
    for(auto &server : servers)
    {
        server.second->stop();
        servers.erase(server.first);
    }
    return true;
}