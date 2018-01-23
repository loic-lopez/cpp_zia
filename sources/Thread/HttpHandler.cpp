//
// Created by loic lopez on 22/01/2018.
//

#include <iostream>
#include <Thread/ThreadPool.hpp>

HttpHandler::HttpHandler() : canStart(false), thread(&HttpHandler::run, this)
{
}

void HttpHandler::run()
{
    while (!canStart);
    this->lock.try_lock();
    ThreadPool::Instance().removeTerminatedThread(refToThreadPool);
    this->lock.unlock();
}

void HttpHandler::setRefToThreadPool(HttpHandler *refToThreadPool)
{
    HttpHandler::refToThreadPool = refToThreadPool;
    canStart = true;
}
