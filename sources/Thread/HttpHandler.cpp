//
// Created by loic lopez on 22/01/2018.
//

#include <Thread/HttpHandler.hpp>
#include <iostream>

HttpHandler::HttpHandler() : thread(&HttpHandler::run, this)
{

}

void HttpHandler::run()
{
    std::cerr << "COUCOU" << std::endl;
}

HttpHandler::~HttpHandler()
{
    this->join();
}
