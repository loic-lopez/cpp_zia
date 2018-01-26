/*
** AnsParser.hpp for cpp_zia in /home/dupil_l/cpp_zia/AnsParser.hpp
**
** Made by Loic DUPIL
** Login   <loic.dupil@epitech.eu>
**
** Started on  Tue Jan 23 15:28:40 2018 Loic DUPIL
** Last update Tue Jan 23 15:28:40 2018 Loic DUPIL
*/
#ifndef CPP_ZIA_ANSPARSER_HPP
#define CPP_ZIA_ANSPARSER_HPP

#include <vector>
#include <map>
#include "IParser.hpp"
#include "Enum.hpp"

class AnsParser :public IParser
{

    std::vector<std::string>    dividedResponseLines;
    std::vector<std::string>    dividedResponseWords;
    zia::api::HttpResponse      response;

public:
    AnsParser();
    ~AnsParser();

    virtual void                parseHttpFormat(std::string);
    virtual void                treatHttp1_1();
    virtual void                fillHeaders(std::string);
    virtual void                getBody();
};

#endif //CPP_ZIA_ANSPARSER_HPP
