//
// Created by loic lopez on 22/01/2018.
//

#include <Thread/ThreadPool.hpp>
#include <iostream>

HttpHandler::HttpHandler() : terminated(false),
                             thread(&HttpHandler::run, this)
{
}

void HttpHandler::run()
{
    while (!terminated)
    {
        if (ThreadPool::Instance().getLock().try_lock())
        {
            ThreadPool::Instance().getLock().unlock();
            break;
        }
    }
    std::cerr << "THREAD RUNNING" << std::endl;
    terminated = true;
}