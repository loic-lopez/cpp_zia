//
// Created by loic lopez on 22/01/2018.
//

#include <Core/ServerCore.hpp>
#include <Thread/ThreadPool.hpp>
#include <iostream>
#include <Core/ServerLauncher.hpp>

HttpHandler::HttpHandler(zia::api::Net::Raw rawData, zia::api::NetInfo netInfo, ServerCoreId serverCoreId) :
        serverCoreId(serverCoreId),
        rawData(std::move(rawData)),
        netInfo(std::move(netInfo))
{
}

void HttpHandler::run()
{
    ServerLauncher::Instance().getServer(serverCoreId)->send(netInfo.sock, zia::api::Net::Raw());
    std::cerr << "RESPONSE SENT!" << std::endl;
#ifdef WIN32
    Sleep(1);
#else
    sleep(1);
#endif
    closesocket(netInfo.sock->socket);
    delete netInfo.sock;
}

HttpHandler::~HttpHandler()
= default;
