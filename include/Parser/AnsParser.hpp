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

#include <Enum.hpp>
#include "IParser.hpp"

class AnsParser :public IParser
{
    AnswerType  type;
    int         returnedCode;
    std::string date;
    std::string server;
    std::string contentType;
    std::string contentLength;
    std::string expires;
    std::string lastModif;

public:
    AnsParser();
    ~AnsParser();

    virtual void parseHttpFormat(std::string);
};

#endif //CPP_ZIA_ANSPARSER_HPP
