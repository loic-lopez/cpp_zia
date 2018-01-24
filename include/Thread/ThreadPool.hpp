//
// Created by loic lopez on 23/01/2018.
//

#ifndef CPP_ZIA_THREADPOOL_HPP
#define CPP_ZIA_THREADPOOL_HPP

#include <memory>
#include <vector>
#include "HttpHandler.hpp"

class ThreadPool
{
private:
    static ThreadPool m_instance;
    std::vector<HttpHandler *> threads;
    std::mutex        lock;
    bool            activeThreadRemover;
    std::thread     threadRemover;

    ThreadPool();
    ~ThreadPool();
    ThreadPool& operator= (const ThreadPool&){}
    ThreadPool (const ThreadPool&) : activeThreadRemover(true), threadRemover(&ThreadPool::handleRemoveTerminatedThreads, this){ };

public:
    static ThreadPool& Instance();
    void addThread();
    void handleRemoveTerminatedThreads();
    bool isEmptyThreadPool();
    void shutdown();

    const std::vector<HttpHandler *> &getThreads() const;
    std::mutex &getLock();

};


#endif //CPP_ZIA_THREADPOOL_HPP
