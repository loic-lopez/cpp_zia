//
// Created by loic lopez on 23/01/2018.
//

#include <iostream>
#include <sys/types.h>
#include <Core/ServerCore.hpp>
#include <fcntl.h>
#include <api/http.h>
#include <Exception/ZiaException.hpp>


ServerCore::ServerCore(ServerCoreId serverCoreId, const zia::api::Conf &conf, zia::api::Net::Callback callback)
        : threadPool(4)
{
#ifdef WIN32
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,2), &WSAData);
#endif

    isRunning = true;
    this->serverCoreId = serverCoreId;
    serverSocket = std::make_shared<zia::api::ImplSocket>();
    serverSocket->socket = socket(AF_INET, SOCK_STREAM, 0);
    try {
        if (serverSocket->socket == INVALID_SOCKET)
            throw ZiaException(ZiaException::errors::CREATE_SOCKET);
    } catch (ZiaException const& e) {
        std::cerr <<  e.what() << std::endl;
        exit(84);
    }


    int opt = 1;
    setsockopt(serverSocket->socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char *>(&opt), sizeof(int));

    this->config(conf);

    this->serverThread = std::make_shared<std::thread>([&]()
                                                       {
                                                           this->run(callback);
                                                       });
}

ServerCore::~ServerCore()
{
    if (serverThread->joinable())
        serverThread->join();
    try {
        closesocket(serverSocket->socket);
    } catch (ZiaException const& e) {
        std::cerr <<  "Unable to close Socket" << std::endl;
         exit(84);
    }

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

    ServerConfig::FormatIPAddress(serverSocket->sockaddr, this->port, this->serverName);
    if (bind(serverSocket->socket, reinterpret_cast<const sockaddr *>(&serverSocket->sockaddr),
             sizeof(serverSocket->sockaddr)) == SOCKET_ERROR)
    {
        std::string msg = "Cannot bind on address: ";
        msg += this->serverName + " with port ";
        msg += std::to_string(this->port);
        throw std::runtime_error(msg);
    }

    if (listen(serverSocket->socket, 32) == SOCKET_ERROR)
        throw std::runtime_error("Cannot listen to socket");

    int newConnection;
    int addrlen = sizeof(serverSocket->sockaddr);
    while (isRunning)
    {
        // TODO: CHANGE TO NON BLOCKING CONNECTION
        this->reset_fds();
        if (select(max_sd + 1, &readfds, nullptr, nullptr, &timeout) > -1)
        {
            if (FD_ISSET(serverSocket->socket, &readfds))
            {
                newConnection = accept(serverSocket->socket, reinterpret_cast<sockaddr *>(&serverSocket->sockaddr),
                                       (socklen_t *) &addrlen);
                if (newConnection != SOCKET_ERROR)
                {
                    std::cout << "accept incomming connection" << std::endl;
                    zia::api::Net::Raw rawData;
                    char Temp[sizeof(zia::api::HttpRequest)] = {'\0'};
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
        }
    }
    return true;
}

bool ServerCore::send(zia::api::ImplSocket *sock, const zia::api::Net::Raw &resp)
{
    std::string response(reinterpret_cast<const char *>(resp.data()));
    ::send(sock->socket, response.c_str(), response.size(), 0);
    return true;
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

ServerCoreId ServerCore::getServerCoreId() const
{
    return serverCoreId;
}

void ServerCore::reset_fds()
{
    FD_ZERO(&readfds);
    FD_SET(serverSocket->socket, &readfds);
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000;
    max_sd = serverSocket->socket;
}

const std::string &ServerCore::getDocumentRootPath() const {
    return documentRootPath;
}
