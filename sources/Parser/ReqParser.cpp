/*
** ReqParser.cpp for cpp_zia in /home/dupil_l/cpp_zia/ReqParser.cpp
**
** Made by Loic DUPIL
** Login   <loic.dupil@epitech.eu>
**
** Started on  Wed Jan 24 10:42:14 2018 Loic DUPIL
** Last update Wed Jan 24 10:42:14 2018 Loic DUPIL
*/

#include <sstream>
#include <sys/stat.h>
#include "Parser/ReqParser.hpp"

ReqParser::ReqParser(std::string _rootfolder) {
    rootfolder = _rootfolder;
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

ReqParser::~ReqParser() {

}

zia::api::HttpResponse ReqParser::parseHttpFormat(std::string httpRequest) {
    std::stringstream line(httpRequest);
    std::string segment;
    std::regex  format { "([A-Z]+) (.+) (HTTP/1.1)" };

    while (std::getline(line, segment, '\n'))
        this->dividedRequestLines.push_back(segment);
    for (const auto &request : dividedRequestLines) {
        std::stringstream line(request);
        while (std::getline(line, segment, ' '))
            this->dividedRequestWords.push_back(segment);
    }
//    for (const auto &version : dividedRequestWords) {
//        if (version.find("HTTP/1.1") != std::string::npos) {
//            treatHttp1_1();
//            break;
//        }
//    }
//  if (std::regex_match(dividedRequestLines[0], format))
 //     {
        if (dividedRequestWords[2].substr(0, 8) == "HTTP/1.1")
           treatHttp1_1();
         else
            createResponse("400", "Wrong HTTP version");
 //  }
 //   else
  //    createResponse("400", "");
    return (response);
}

// a transformer en zia::api::HttpRequest
void ReqParser::treatHttp1_1() {
    std::string potentialError = "";
    std::string errorReason = "";

    this->request.version = zia::api::http::Version::http_1_1;
    this->path = this->dividedRequestWords[1];
    for (const auto &method : this->dividedRequestWords) {
            this->request.method = this->type[method];
        if (method.at(method.size() - 1) == ':') {
            fillHeaders(method);
        }

    }
    this->createResponse(potentialError, errorReason);
}

void ReqParser::fillHeaders(std::string toFind) {
    for (const auto &headers : this->dividedRequestLines) {
        if (headers.find(toFind) != std::string::npos) {
            this->request.headers.insert({toFind, headers.substr(toFind.size() + 1)});
            if (toFind == "Host:")
                this->request.uri = headers.substr(toFind.size() + 1);
        }
    }
}

void ReqParser::getBody(size_t i) {

}

void ReqParser::createResponse(std::string potentialError, std::string errorReason) {
    if (potentialError.length() > 0 && errorReason.length() > 0) {
        if (std::stoi(potentialError) == 400) {

            this->response.status = zia::api::http::common_status::bad_request;
            this->response.reason = "Bad request";
            for (unsigned int i = 0; i < errorReason.length(); i++) {
                char c = errorReason[i];
                std::byte uc = static_cast<std::byte>(c);
                this->response.body.push_back(uc);
            }
        }
    }
    if (this->path.size() > 0) {
        if (path == "/")
            path = "/index.html";
        if (this->request.version == zia::api::http::Version::http_1_1)
            this->response.version = zia::api::http::Version::http_1_1;
        std::string temp_path;
        std::string final_path = rootfolder;
        temp_path = this->path.substr(this->path.find_last_of("/") + 1);
        final_path += temp_path;
        path = final_path;
        if (this->fileExists()) {
            std::ifstream myFile(this->path);
            if (myFile.good()) {
                char c;
                while (myFile.get(c)) {
                    std::byte uc = static_cast<std::byte>(c);
                    this->response.body.push_back(uc);
                }
                this->response.status = zia::api::http::common_status::ok;
                this->response.reason = "OK";
            } else {
                this->response.status = zia::api::http::common_status::forbidden;
                this->response.reason = "Forbidden";
            }
        } else {
            this->response.status = zia::api::http::common_status::not_found;
            this->response.reason = "Not found";
        }
    }
    this->fillResponseHeader();
}

void ReqParser::fillResponseHeader() {
    this->response.headers.insert({"Server: ", "Zia"});
    this->response.headers.insert({"Content-Length: ", std::to_string(this->response.body.size())});
    this->response.headers.insert({"Content-Type: ", "text/html"});
    this->response.headers.insert({"Connection: ", "close"});

}

bool ReqParser::fileExists() {
    struct stat buffer;
    return (stat(this->path.c_str(), &buffer) == 0);
}

