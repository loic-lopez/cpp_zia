/*
** ReqParser.cpp for cpp_zia in /home/dupil_l/cpp_zia/ReqParser.cpp
**
** Made by Loic DUPIL
** Login   <loic.dupil@epitech.eu>
**
** Started on  Wed Jan 24 10:42:14 2018 Loic DUPIL
** Last update Wed Jan 24 10:42:14 2018 Loic DUPIL
*/

#include "Parser/ReqParser.hpp"

ReqParser::ReqParser()
{

}

ReqParser::~ReqParser()
{

}

void ReqParser::parseHttpFormat(std::string httpRequest)
{
    std::string line;
    std::size_t pos;
    std::size_t lastPos = 0;

    while (pos != std::string::npos)
    {
        httpRequest.find("\n", pos);
        std::cout << std::endl;
        //std::cout << httpRequest.substr(lastPos, pos) << std::endl;
            //this->dividedRequest.emplace_back(httpRequest.substr(lastPos, pos));
            lastPos = pos + 1;
    }
    for (int i = 0; i < this->dividedRequest.size(); ++i)
    {
        std::cout << this->dividedRequest[i] << std::endl;
    }
}
