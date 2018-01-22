//
// Created by loic lopez on 22/01/2018.
//

#include <Thread/HttpHandler.hpp>
#include <iostream>

HttpHandler::HttpHandler(std::function<void()> function) : thread(function)
{

}

HttpHandler::~HttpHandler()
{
    this->join();
}
