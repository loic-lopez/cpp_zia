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
#include "IParser.hpp"
#include "Enum.hpp"

class ReqParser : public IParser
{
    std::vector<std::string>    dividedRequestLines;
    std::vector<std::string>    dividedRequestWords;
    zia::api::HttpRequest       request;
    std::map<std::string, zia::api::http::Method>   type;
    std::string                 path;

public:
    ReqParser();
    ~ReqParser();

    virtual void    parseHttpFormat(std::string);
    virtual void    treatHttp1_1();
    void            fillHearders(std::string);
    void            getBody(size_t);

};

#endif //CPP_ZIA_REQPARSER_HPP
