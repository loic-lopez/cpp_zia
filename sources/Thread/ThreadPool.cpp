//
// Created by loic lopez on 23/01/2018.
//

#include <Thread/ThreadPool.hpp>
#include <iostream>
#include <Core/ServerCore.hpp>

ThreadPool ThreadPool::m_instance = ThreadPool();

ThreadPool &ThreadPool::Instance()
{
    return m_instance;
}

ThreadPool::ThreadPool() : activeThreadRemover(true),
                           threadRemover(&ThreadPool::handleRemoveTerminatedThreads, this)
{
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::addThread()
{
    while (!this->lock.try_lock());
    this->threads.emplace_back(new HttpHandler());
    lock.unlock();
}

const std::vector<HttpHandler *> &ThreadPool::getThreads() const
{
    return threads;
}

void ThreadPool::handleRemoveTerminatedThreads()
{
    while (activeThreadRemover)
    {
        if (this->lock.try_lock())
        {
            for (auto thread : threads)
            {
                if (thread->terminated)
                {
                    thread->join();
                    this->threads.erase(std::remove(threads.begin(), threads.end(), thread), threads.end());
                    delete thread;
                    break;
                }
            }
            lock.unlock();
        }
    }
}

bool ThreadPool::isEmptyThreadPool()
{
    while (!this->lock.try_lock());
    bool empty = threads.empty();
    lock.unlock();
    return empty;
}

void ThreadPool::shutdown()
{
    activeThreadRemover = false;
    threadRemover.join();
}
