//
// Created by loic lopez on 22/01/2018.
//

#include <Thread/ThreadPool.hpp>
#include <Core/ServerCore.hpp>
#include <iostream>

HttpHandler::HttpHandler() : terminated(false),
                             lock(ServerCore::Instance().getLock()),
                             thread(&HttpHandler::run, this)
{
}

void HttpHandler::run()
{
    while (!terminated)
    {
        if (this->lock.try_lock())
        {
            this->lock.unlock();
            terminated = true;
        }
    }
    std::cerr << "THREAD RUNNING" << std::endl;
}