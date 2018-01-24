//
// Created by loic lopez on 23/01/2018.
//

#ifndef CPP_ZIA_SERVERCORE_HPP
#define CPP_ZIA_SERVERCORE_HPP

#include <Static/ServerConfig.hpp>
#include <Thread/ThreadPool.hpp>

class ServerCore
{
private:
    static ServerCore m_instance;
    ThreadPool  &threadPool;
    std::mutex lock;

    ServerCore& operator= (const ServerCore&){}
    ServerCore (const ServerCore&) : threadPool(ThreadPool::Instance())
    {

    };

    ServerCore();
    ~ServerCore();

public:
    static ServerCore& Instance();
    void run();

    std::mutex &getLock();

};


#endif //CPP_ZIA_SERVERCORE_HPP
