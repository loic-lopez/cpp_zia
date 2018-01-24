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
    this->type.insert({"GET", zia::api::http::Method::get});
    this->type.insert({"OPTIONS", zia::api::http::Method::options});
    this->type.insert({"HEAD", zia::api::http::Method::head});
    this->type.insert({"POST", zia::api::http::Method::post});
    this->type.insert({"PUT", zia::api::http::Method::put});
    this->type.insert({"DELETE", zia::api::http::Method::delete_});
    this->type.insert({"TRACE", zia::api::http::Method::trace});
    this->type.insert({"CONNECT", zia::api::http::Method::connect});
    this->type.insert({"UNKNOWN", zia::api::http::Method::unknown});
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
    this->request.version = zia::api::http::Version::http_1_1;
    this->request.method = this->type[this->dividedRequestWords[0]];

}