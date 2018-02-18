/*
** ReqParser.hpp for cpp_zia in /home/dupil_l/cpp_zia/ReqParser.hpp
**
** Made by Loic DUPIL
** Login   <loic.dupil@epitech.eu>
**
** Started on  Tue Jan 23 13:58:00 2018 Loic DUPIL
** Last update Tue Jan 23 13:58:00 2018 Loic DUPIL
*/
#ifndef CPP_ZIA_REQPARSER_HPP
#define CPP_ZIA_REQPARSER_HPP

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <iterator>
#include <streambuf>
#include <api/http.h>
#include "Enum.hpp"

class ReqParser
{
    std::vector<std::string>                        dividedRequestLines;
    std::vector<std::string>                        dividedRequestWords;
    zia::api::HttpRequest                           request;
    std::map<std::string, zia::api::http::Method>   type;
    std::string                                     path;
    zia::api::HttpResponse                          response;

public:
    ReqParser();
    ~ReqParser();

    zia::api::HttpResponse     parseHttpFormat(std::string);
    void    treatHttp1_1();
    void    fillHeaders(std::string);
    void    getBody(size_t);
    void    createResponse();
    void    fillResponseHeader();
    bool    fileExists();

};

#endif //CPP_ZIA_REQPARSER_HPP
