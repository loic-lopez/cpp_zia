/*
** IParser.hpp for cpp_zia in /home/dupil_l/cpp_zia/IParser.hpp
**
** Made by Loic DUPIL
** Login   <loic.dupil@epitech.eu>
**
** Started on  Tue Jan 23 13:59:27 2018 Loic DUPIL
** Last update Tue Jan 23 13:59:27 2018 Loic DUPIL
*/
#ifndef CPP_ZIA_IPARSER_HPP
#define CPP_ZIA_IPARSER_HPP

#include <string>
#include <iostream>
#include <fstream>

class IParser
{
public:
    ~IParser(){};

    virtual void parseHttpFormat(std::string) = 0;

};

#endif //CPP_ZIA_IPARSER_HPP
