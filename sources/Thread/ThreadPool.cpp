//
// Created by loic lopez on 23/01/2018.
//

#include <Thread/ThreadPool.hpp>
#include <iostream>

ThreadPool ThreadPool::m_instance = ThreadPool();

ThreadPool &ThreadPool::Instance()
{
    return m_instance;
}

ThreadPool::ThreadPool()
{

}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::addThread()
{
    this->threads.emplace_back(new HttpHandler());
    this->threads.back()->setRefToThreadPool(this->threads.back());
}

const std::vector<HttpHandler *> &ThreadPool::getThreads() const
{
    return threads;
}

void ThreadPool::removeTerminatedThread(HttpHandler *threadRef)
{
    this->threads.erase(std::remove(threads.begin(), threads.end(), threadRef), threads.end());
    threadRef->join();
    delete threadRef;
}
