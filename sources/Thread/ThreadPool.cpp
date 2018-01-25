//
// Created by loic lopez on 23/01/2018.
//

#include <Thread/ThreadPool.hpp>
#include <iostream>
#include <Core/ServerCore.hpp>

ThreadPool::ThreadPool() : activeThreadRemover(true),
                           threadRemover(&ThreadPool::handleRemoveTerminatedThreads, this)
{
}

std::mutex &ThreadPool::getLock()
{
    return lock;
}


ThreadPool::~ThreadPool()
{
    activeThreadRemover = false;
}

void ThreadPool::addThread(zia::api::Net::Raw rawData, zia::api::NetInfo netInfo)
{
    this->threads.emplace_back(new HttpHandler(std::move(rawData), std::move(netInfo), serverCoreId));
}

void ThreadPool::handleRemoveTerminatedThreads()
{
    while (activeThreadRemover)
    {
        if (!threads.empty() && this->lock.try_lock())
        {
            for (int i = 0; i < threads.size(); ++i)
            {
                HttpHandler *thread = threads.at(i);
                if (thread->terminated)
                {
                    thread->join();
                    this->threads.erase(std::remove(threads.begin(), threads.end(), thread), threads.end());
                    delete thread;
                    lock.unlock();
                    break;
                }
            }
        }
    }
}

void ThreadPool::shutdown()
{
    activeThreadRemover = false;
    threadRemover.join();
}

void ThreadPool::setServerCoreId(ServerCoreId serverCoreId)
{
    ThreadPool::serverCoreId = serverCoreId;
}
