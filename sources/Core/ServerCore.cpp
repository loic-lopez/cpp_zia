//
// Created by loic lopez on 23/01/2018.
//

#include <iostream>
#include <Core/ServerCore.hpp>

ServerCore ServerCore::m_instance = ServerCore();

ServerCore::ServerCore() : threadPool(ThreadPool::Instance())
{
#if defined (WIN32)
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,2), &WSAData);
#endif
    serverSocket = std::shared_ptr<ImplSocket>(new ImplSocket());
    serverSocket->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket->socket == INVALID_SOCKET)
        throw std::exception();
    serverSocket->sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverSocket->sockaddr.sin_family = AF_INET;
    serverSocket->sockaddr.sin_port = htons(static_cast<u_short>(static_cast<int>(std::get<long long>(ServerConfig::ServerPort.v))));
    bind(serverSocket->socket, reinterpret_cast<struct sockaddr *>(&serverSocket->sockaddr), sizeof(serverSocket->sockaddr));
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
    listen(serverSocket->socket, 32);
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

