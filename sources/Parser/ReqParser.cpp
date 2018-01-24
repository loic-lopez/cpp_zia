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
    std::stringstream   line(httpRequest);
    std::string         segment;

    while (std::getline(line, segment, '\n'))
        this->dividedRequestLines.push_back(segment);

    for (const auto &request : dividedRequestLines)
    {
        std::stringstream   line(request);
        while (std::getline(line, segment, ' '))
            this->dividedRequestWords.push_back(segment);
    }
    for (const auto &version : dividedRequestWords)
    {
        if (version.find("HTTP/1.1") != std::string::npos)
        {
            treatHttp1_1();
            break;
        }
    }
}

void ReqParser::treatHttp1_1()
{

}
