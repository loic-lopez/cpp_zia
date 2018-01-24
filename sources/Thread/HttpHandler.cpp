//
// Created by loic lopez on 22/01/2018.
//

#include <Thread/ThreadPool.hpp>
#include <Core/ServerCore.hpp>
#include <iostream>

HttpHandler::HttpHandler() : terminated(false),
                             thread(&HttpHandler::run, this)
{
}

void HttpHandler::run()
{
    while (!terminated)
    {
        if (ServerCore::Instance().getLock().try_lock())
        {
            ServerCore::Instance().getLock().unlock();
            break;
        }
    }
    std::cerr << "THREAD RUNNING" << std::endl;
    terminated = true;
}