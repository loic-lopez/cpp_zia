//
// Created by loic lopez on 23/01/2018.
//

#ifndef CPP_ZIA_THREADPOOL_HPP
#define CPP_ZIA_THREADPOOL_HPP

#include <memory>
#include <vector>
#include <api/net.h>
#include <Static/ServerConfig.hpp>
#include <queue>
#include "HttpHandler.hpp"

class ThreadPool
{
private:
    std::mutex 			lock_;
    std::condition_variable	condVar_;
    bool 				shutdown_;
    std::queue<std::function <void ()>> jobs_;
    std::vector<std::thread> 	threads_;
    ServerCoreId   serverCoreId;

public:
    explicit ThreadPool(int nbThreads);
    ~ThreadPool();
    ThreadPool& operator= (const ThreadPool&){}
    ThreadPool (const ThreadPool&) { };


    void 				doJob(std::function <void ()> func);
    void	            threadRun(void);

};


#endif //CPP_ZIA_THREADPOOL_HPP
