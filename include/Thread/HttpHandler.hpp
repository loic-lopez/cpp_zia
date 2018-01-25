//
// Created by loic lopez on 22/01/2018.
//

#ifndef CPP_ZIA_HTTPHANDLER_HPP
#define CPP_ZIA_HTTPHANDLER_HPP

#include <functional>
#include <thread>
#include <mutex>
#include <Core/ImplSocket.hpp>

class HttpHandler : public std::thread
{
public:

    explicit HttpHandler(zia::api::Net::Raw rawData, zia::api::NetInfo netInfo, ServerCoreId serverCoreId);
    void     run();

    bool terminated;
    zia::api::Net::Raw rawData;
    zia::api::NetInfo netInfo;
    ServerCoreId serverCoreId;
};


#endif //CPP_ZIA_HTTPHANDLER_HPP
