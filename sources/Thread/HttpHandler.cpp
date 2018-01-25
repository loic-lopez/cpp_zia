//
// Created by loic lopez on 22/01/2018.
//

#include <Core/ServerCore.hpp>
#include <Thread/ThreadPool.hpp>
#include <iostream>

HttpHandler::HttpHandler(zia::api::Net::Raw rawData, zia::api::NetInfo netInfo) :
        rawData(std::move(rawData)),
        netInfo(std::move(netInfo)),
        terminated(false),
        thread(&HttpHandler::run, this)
{
}

void HttpHandler::run()
{
    while (true)
    {
        if (ThreadPool::Instance().getLock().try_lock())
        {
            //ServerCore::Instance().send(/* insert socket and response*/);
            // SAMPLE OF HTTP HERE !!!!!!!!!!!!!! TODO: REPLACE WITH REAL PARSER AND REAL RESPONSE

            std::ifstream ifs("html/index.html");
            std::string content( (std::istreambuf_iterator<char>(ifs) ),
                                 (std::istreambuf_iterator<char>()    ) );

            ifs.close();
            std::time_t t = std::chrono::system_clock::to_time_t(netInfo.time);
            std::string header =
                    std::string("HTTP/1.1 200 OK\r\n") +
                            std::string("Date: ") + std::string(std::ctime(&t)) +
                            std::string("Server: Zia\r\n") +
                            std::string("Content-Length: ") + std::to_string(content.size()) + "\r\n" +
                            std::string("Content-Type: text/html\r\n") +
                            std::string("Connection: Close\r\n") + "\r\n";

            send(netInfo.sock->socket, header.c_str(), header.size(), 0);
            send(netInfo.sock->socket, content.c_str(), content.size(), 0);

            ThreadPool::Instance().getLock().unlock();
            break;
        }
    }
    std::cerr << "RESPONSE SENT!" << std::endl;
    closesocket(netInfo.sock->socket);
    delete netInfo.sock;
    terminated = true;
}