//
// Created by loic lopez on 22/01/2018.
//

#include <Thread/HttpHandler.hpp>
#include <iostream>

HttpHandler::HttpHandler() : thread(&HttpHandler::run, this)
{

}

HttpHandler::~HttpHandler()
{
    this->join();
}

void HttpHandler::run()
{
    std::cerr << "COUCOU" << std::endl;
}
