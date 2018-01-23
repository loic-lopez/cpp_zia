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

    ThreadPool();
    ~ThreadPool();
    ThreadPool& operator= (const ThreadPool&){}
    ThreadPool (const ThreadPool&) = default;

public:
    static ThreadPool& Instance();
    void addThread();
    void removeTerminatedThread(HttpHandler *thread);

    const std::vector<HttpHandler *> &getThreads() const;

};


#endif //CPP_ZIA_THREADPOOL_HPP
