//
// Created by loic lopez on 22/01/2018.
//

#ifndef CPP_ZIA_HTTPHANDLER_HPP
#define CPP_ZIA_HTTPHANDLER_HPP

#include <functional>
#include <thread>
#include <mutex>

class HttpHandler : public std::thread
{
private:
    std::mutex  lock;
    HttpHandler *refToThreadPool;
    bool canStart;

public:
    explicit HttpHandler();
    void     run();
    void setRefToThreadPool(HttpHandler *refToThreadPool);
};


#endif //CPP_ZIA_HTTPHANDLER_HPP
