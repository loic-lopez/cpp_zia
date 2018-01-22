//
// Created by loic lopez on 22/01/2018.
//

#ifndef CPP_ZIA_HTTPHANDLER_HPP
#define CPP_ZIA_HTTPHANDLER_HPP

#include <functional>
#include <thread>

class HttpHandler : public std::thread
{
public:
    explicit HttpHandler(std::function<void()> function);
    ~HttpHandler();
};


#endif //CPP_ZIA_HTTPHANDLER_HPP
