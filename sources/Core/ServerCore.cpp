//
// Created by loic lopez on 23/01/2018.
//

#include <iostream>
#include <Core/ServerCore.hpp>

ServerCore ServerCore::m_instance = ServerCore();

ServerCore::ServerCore() : threadPool(ThreadPool::Instance())
{
    if (ServerConfig::isConfigFileExists("toto"))
        std::cout << "found" << std::endl;
    else
        std::cout << "not found" << std::endl;
}

ServerCore::~ServerCore()
{

}

void ServerCore::run()
{
    for (int i = 0; i < 5; ++i)
    {
        threadPool.addThread();
    }
    std::cout << threadPool.getThreads().size() << std::endl;
}

ServerCore &ServerCore::Instance()
{
    return m_instance;
}
