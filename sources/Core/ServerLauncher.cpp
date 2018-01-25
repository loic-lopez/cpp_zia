//
// Created by loic lopez on 25/01/2018.
//

#include <Core/ServerLauncher.hpp>

ServerLauncher ServerLauncher::m_instance = ServerLauncher();


ServerLauncher &ServerLauncher::Instance()
{
    return m_instance;
}

ServerLauncher::ServerLauncher()
{

}

ServerLauncher::~ServerLauncher()
{

}


void ServerLauncher::launch()
{

}