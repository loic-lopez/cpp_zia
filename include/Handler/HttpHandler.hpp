//
// Created by loic lopez on 22/01/2018.
//

#ifndef CPP_ZIA_HTTPHANDLER_HPP
#define CPP_ZIA_HTTPHANDLER_HPP

#include <functional>
#include <thread>
#include <mutex>
#include <Core/ImplSocket.hpp>
#include <Static/ServerConfig.hpp>
#include <api/net.h>

class HttpHandler
{
private:
    zia::api::Net::Raw rawData;
    zia::api::NetInfo netInfo;
    ServerCoreId serverCoreId;
    std::string  documentRootPath;

public:
    explicit HttpHandler(zia::api::Net::Raw rawData, zia::api::NetInfo netInfo, const std::string &documentRootPath, ServerCoreId serverCoreId);

    virtual ~HttpHandler();

    void     run();
};


#endif //CPP_ZIA_HTTPHANDLER_HPP
