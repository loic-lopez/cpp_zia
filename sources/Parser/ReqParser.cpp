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
    this->path = this->dividedRequestWords[1];
    for (const auto &method : this->dividedRequestWords)
    {
        if (this->type.find(method) != this->type.end())
            this->request.method = this->type[method];
        if (method.at(method.size() - 1) == ':')
            fillHeaders(method);
    }
    //TODO: a finir récupération du body
//    size_t i = 0;
//    for (std::vector<std::string>::iterator it = this->dividedRequestLines.begin(); it < this->dividedRequestLines.end() ; ++it)
//    {
//        if ((*it) == "\n")
//        {
//            getBody(i);
//            i++;
//            break;
//        }
//        i++;
//    }
}

void ReqParser::fillHeaders(std::string toFind)
{
    for (const auto &headers : this->dividedRequestLines)
    {
        if (headers.find(toFind) != std::string::npos)
        {
            this->request.headers.insert({toFind, headers.substr(toFind.size() + 1)});
            if (toFind == "Host:")
                this->request.uri = headers.substr(toFind.size() + 1);
        }
    }
}

void ReqParser::getBody(size_t i)
{

}
