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
#include "IParser.hpp"
#include "Enum.hpp"

class ReqParser : public IParser
{
    HttpRequestType type;
    std::string     host;
    std::string     referer;
    std::string     userAgent;
    //Request's content

    std::vector<std::string>    dividedRequest;
public:
    ReqParser();
    ~ReqParser();

    virtual void parseHttpFormat(std::string);

};

#endif //CPP_ZIA_REQPARSER_HPP
