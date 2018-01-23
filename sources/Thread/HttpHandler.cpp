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
    while (!this->lock.try_lock());
    std::cerr << "THREAD RUNNING" << std::endl;
    this->lock.unlock();
    terminated = true;
}