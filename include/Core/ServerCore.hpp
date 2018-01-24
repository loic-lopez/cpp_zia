//
// Created by loic lopez on 23/01/2018.
//

#ifndef CPP_ZIA_SERVERCORE_HPP
#define CPP_ZIA_SERVERCORE_HPP

#include <Static/ServerConfig.hpp>
#include <Thread/ThreadPool.hpp>
#include <api/net.h>

class ServerCore : public  zia::api::Net
{
private:
    static ServerCore m_instance;
    ThreadPool  &threadPool;

    ServerCore& operator= (const ServerCore&){}
    ServerCore (const ServerCore&) : threadPool(ThreadPool::Instance())
    {

    };

    ServerCore();
    ~ServerCore();

public:
    static ServerCore& Instance();
    void run();
    virtual bool config(const zia::api::Conf& conf);
    virtual bool run(Callback cb);
    virtual bool send(zia::api::ImplSocket* sock, const Raw& resp);
    virtual bool stop();
};


#endif //CPP_ZIA_SERVERCORE_HPP
