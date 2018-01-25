//
// Created by loic lopez on 23/01/2018.
//

#include <iostream>
#include <Core/ServerCore.hpp>

ServerCore ServerCore::m_instance = ServerCore();

ServerCore::ServerCore() : threadPool(ThreadPool::Instance())
{
#ifdef WIN32
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,2), &WSAData);
#endif

    serverSocket = std::make_shared<ImplSocket>();
    serverSocket->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket->socket == INVALID_SOCKET)
        throw std::runtime_error("Cannot create socket.");
}

ServerCore::~ServerCore()
{
    closesocket(serverSocket->socket);
#if defined (WIN32)
    WSACleanup();
#endif
}

ServerCore &ServerCore::Instance()
{
    return m_instance;
}

bool ServerCore::config(const zia::api::Conf &conf) {
    if (ServerConfig::isConfigFileExists())
        return true;
    else
        return false;
}

bool ServerCore::run(zia::api::Net::Callback callback) {
   /* for (int i = 0; i < 10; ++i)
    {
        zia::api::NetInfo netInfo;
        callback(zia::api::Net::Raw(), netInfo);
    }*/

#if defined(__APPLE__) || defined(__linux__)
    long long port = std::get<long long>(ServerConfig::ServerPort.v);
    if (getuid() && port == 80 || port == 443)
        throw std::runtime_error("You must run zia with admin right with requested port : " + std::to_string(port));
#endif

    struct sockaddr finalAddr = ServerConfig::FormatIPAdress(serverSocket->sockaddr);
    if (bind(serverSocket->socket, &finalAddr, sizeof(serverSocket->sockaddr)) == -1)
    {
        std::string msg = "Cannot bind on address: ";
        msg += std::get<std::string>(ServerConfig::ServerIP.v) + " with port ";
        msg += std::to_string(std::get<long long>(ServerConfig::ServerPort.v));
        throw std::runtime_error(msg);
    }

    if (listen(serverSocket->socket, 32) == -1)
        throw std::exception();

    while (true)
    {
        if (threadPool.isEmptyThreadPool())
        {
            threadPool.shutdown();
            std::cout << threadPool.getThreads().size() << std::endl;
            break;
        }
        std::cout << threadPool.getThreads().size() << std::endl;
    }

    std::cout << "all job  terminated" << std::endl;
    return true;
}

bool ServerCore::send(zia::api::ImplSocket *sock, const zia::api::Net::Raw &resp) {

    return false;
}

bool ServerCore::stop() {
    return false;
}