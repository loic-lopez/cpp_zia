//
// Created by loic lopez on 23/01/2018.
//

#ifndef CPP_ZIA_THREADPOOL_HPP
#define CPP_ZIA_THREADPOOL_HPP

#include <memory>
#include <vector>
#include <api/net.h>
#include "HttpHandler.hpp"

class ThreadPool
{
private:
    std::vector<HttpHandler *> threads;
    std::mutex        lock;
    bool            activeThreadRemover;
    std::thread     threadRemover;


public:
    ThreadPool();
    ~ThreadPool();
    ThreadPool& operator= (const ThreadPool&){}
    ThreadPool (const ThreadPool&) : activeThreadRemover(true), threadRemover(&ThreadPool::handleRemoveTerminatedThreads, this){ };

    void addThread(zia::api::Net::Raw rawData, zia::api::NetInfo netInfo);
    void handleRemoveTerminatedThreads();
    void shutdown();
    std::mutex &getLock();

};


#endif //CPP_ZIA_THREADPOOL_HPP
