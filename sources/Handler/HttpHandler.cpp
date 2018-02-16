//
// Created by loic lopez on 22/01/2018.
//

#include <Core/ServerCore.hpp>
#include <Core/ServerLauncher.hpp>

HttpHandler::HttpHandler(zia::api::Net::Raw rawData, zia::api::NetInfo netInfo,  const std::string &documentRootPath, ServerCoreId serverCoreId) :
        serverCoreId(serverCoreId),
        documentRootPath(documentRootPath),
        rawData(std::move(rawData)),
        netInfo(std::move(netInfo))
{
}

void HttpHandler::run()
{
    //create the parser
    //convert rawData tostring
    //parsehttpformat

    // use document root path

    // AnsParser
    //cf la fonction send pour modele de header

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
