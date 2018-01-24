//
// Created by loic lopez on 23/01/2018.
//

#include <iostream>
#include <Core/ServerCore.hpp>

ServerCore ServerCore::m_instance = ServerCore();

ServerCore::ServerCore() : threadPool(ThreadPool::Instance())
{
}

ServerCore::~ServerCore()
{
}

ServerCore &ServerCore::Instance()
{
    return m_instance;
}

bool ServerCore::config(const zia::api::Conf &conf) {
    if (ServerConfig::isConfigFileExists())
        return true;
    else
        return false;
}

bool ServerCore::run(zia::api::Net::Callback callback) {
    for (int i = 0; i < 10; ++i)
    {
        zia::api::NetInfo netInfo;
        callback(zia::api::Net::Raw(), netInfo);
    }
    while (true)
    {
        if (threadPool.isEmptyThreadPool())
        {
            threadPool.shutdown();
            std::cout << threadPool.getThreads().size() << std::endl;
            break;
        }
        std::cout << threadPool.getThreads().size() << std::endl;
    }

    std::cout << "all job terminated" << std::endl;
    return true;
}

bool ServerCore::send(zia::api::ImplSocket *sock, const zia::api::Net::Raw &resp) {

    return false;
}

bool ServerCore::stop() {
    return false;
}

