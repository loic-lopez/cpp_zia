//
// Created by loic lopez on 23/01/2018.
//

#include <iostream>
#include <Core/ServerCore.hpp>

ServerCore::ServerCore(ServerCoreId serverCoreId, const zia::api::Conf &conf, zia::api::Net::Callback callback)
{
#ifdef WIN32
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,2), &WSAData);
#endif

    isRunning = true;
    this->serverCoreId = serverCoreId;
    serverSocket = std::make_shared<zia::api::ImplSocket>();
    serverSocket->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket->socket == INVALID_SOCKET)
        throw std::runtime_error("Cannot create socket.");
    config(conf);
    this->serverThread = std::make_shared<std::thread>([&]()
                                                       {
                                                           this->run(callback);
                                                       });
}

ServerCore::~ServerCore()
{
    serverThread->join();
    closesocket(serverSocket->socket);
#if defined (WIN32)
    WSACleanup();
#endif
}

bool ServerCore::config(const zia::api::Conf &conf)
{

    this->port = std::get<long long>(conf.at("port").v);
    this->serverName = std::get<std::string>(conf.at("server_name").v);
    this->documentRootPath = std::get<std::string>(conf.at("document_root").v);

    return false;
}

bool ServerCore::run(zia::api::Net::Callback callback)
{

#if defined(__APPLE__) || defined(__linux__)
    if (getuid() && this->port == 80 || this->port == 443)
        throw std::runtime_error(
                "You must isRunning zia with admin right with requested port : " + std::to_string(port));
#endif

    struct sockaddr finalAddr = ServerConfig::FormatIPAddress(serverSocket->sockaddr, this->port, this->serverName);
    if (bind(serverSocket->socket, &finalAddr, sizeof(serverSocket->sockaddr)) == SOCKET_ERROR)
    {
        std::string msg = "Cannot bind on address: ";
        msg += this->serverName + " with port ";
        msg += std::to_string(this->port);
        throw std::runtime_error(msg);
    }

    if (listen(serverSocket->socket, 32) == SOCKET_ERROR)
        throw std::runtime_error("Cannot listen to socket");

    int newConnection;
    while (isRunning)
    {
        newConnection = accept(serverSocket->socket, nullptr, nullptr);
        if (newConnection != SOCKET_ERROR)
        {
            std::cout << "accept incomming connection" << std::endl;
            zia::api::Net::Raw rawData;
            char Temp[10000] = {'\0'};
            if (recv(newConnection, Temp, sizeof(Temp), 0) != SOCKET_ERROR)
            {
                for (int j = 0; Temp[j] != 0; ++j)
                    rawData.push_back(std::byte(Temp[j]));

                zia::api::NetInfo netInfo;
                netInfo.sock = new zia::api::ImplSocket(newConnection);
                netInfo.time = std::chrono::system_clock::now();
                netInfo.start = std::chrono::steady_clock::now();
                callback(rawData, netInfo);
            }

        }
    }
    threadPool.shutdown();
    return true;
}

bool ServerCore::send(zia::api::ImplSocket *sock, const zia::api::Net::Raw &resp)
{

    return false;
}

bool ServerCore::stop()
{

    isRunning = false;
    return true;
}

ThreadPool &ServerCore::getThreadPool()
{
    return threadPool;
}
