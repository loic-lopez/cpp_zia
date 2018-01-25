//
// Created by loic lopez on 23/01/2018.
//

#ifndef CPP_ZIA_SERVERCORE_HPP
#define CPP_ZIA_SERVERCORE_HPP

#include <Static/ServerConfig.hpp>
#include <Thread/ThreadPool.hpp>
#include <api/net.h>
#include <memory>
#include "ImplSocket.hpp"

class ServerCore : public zia::api::Net
{
private:
    ThreadPool  threadPool;
    std::shared_ptr<zia::api::ImplSocket> serverSocket;
    std::string  webRootPath;
    int          port;


public:

    ServerCore();
    ~ServerCore();

    bool config(const zia::api::Conf& conf) override;

    bool run(Callback cb) override;

    bool send(zia::api::ImplSocket* sock, const Raw& resp) override;

    bool stop() override;

    ThreadPool &getThreadPool();
};


#endif //CPP_ZIA_SERVERCORE_HPP
