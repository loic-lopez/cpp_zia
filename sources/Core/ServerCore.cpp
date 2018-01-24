//
// Created by loic lopez on 23/01/2018.
//

#include <iostream>
#include <Core/ServerCore.hpp>

ServerCore ServerCore::m_instance = ServerCore();

ServerCore::ServerCore() : threadPool(ThreadPool::Instance())
{
    if (ServerConfig::isConfigFileExists())
        ServerConfig::LoadConfigFromFile();
    else
        std::cout << "not found" << std::endl;
}

ServerCore::~ServerCore()
{
}

void ServerCore::run()
{
    for (int i = 0; i < 10; ++i)
    {
        threadPool.addThread();
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

}

ServerCore &ServerCore::Instance()
{
    return m_instance;
}