//
// Created by loic lopez on 22/01/2018.
//

#include <Core/ServerCore.hpp>
#include <Core/ServerLauncher.hpp>
#include <Parser/ReqParser.hpp>

HttpHandler::HttpHandler(zia::api::Net::Raw rawData, zia::api::NetInfo netInfo,  const std::string &documentRootPath, ServerCoreId serverCoreId) :
        serverCoreId(serverCoreId),
        documentRootPath(documentRootPath),
        rawData(std::move(rawData)),
        netInfo(std::move(netInfo))
{
}

void HttpHandler::run()
{
if (!rawData.empty()) {
    std::string fullReq(reinterpret_cast<char *>(rawData.data()));
    ReqParser clientQuest(documentRootPath);
    zia::api::HttpResponse resp = clientQuest.parseHttpFormat(fullReq);
    std::string header;
    zia::api::Net::Raw respRaw;
    if (resp.status == zia::api::http::common_status::ok) {
        header += std::string("HTTP/1.1 200 OK\r\n");
        header += "Server: " + resp.headers["Server: "] + "\r\n";
        header += "Content-Length: " + resp.headers["Content-Length: "] + "\r\n";
        header += "Content-Type: " + resp.headers["Content-Type: "] + "\r\n";
        header += "Connection: " + resp.headers["Connection: "] + "\r\n";
        header += std::string("Connection: close\r\n")+ "\r\n";
        for (size_t i = 0; i < header.size(); i++)
            respRaw.push_back((std::byte)header[i]);
        for (size_t i = 0; i < resp.body.size(); i++)
            respRaw.push_back(resp.body[i]);
    } else if (resp.status == zia::api::http::common_status::not_found) {
        std::string notFound("<html><body><h1>Error 404</h1>File not found</body></html>");
        header += std::string("HTTP/1.1 200 OK\r\n");
        header += "Server: " + resp.headers["Server: "] + "\r\n";
        header += "Content-Length: " + std::to_string(notFound.size()) + "\r\n";
        header += std::string("Content-Type: text/html\r\n");
        header += std::string("Connection: close\r\n")+ "\r\n";
        header += notFound;
        for (size_t i = 0; i < header.size(); i++)
            respRaw.push_back((std::byte)header[i]);
    } else if (resp.status == zia::api::http::common_status::forbidden) {
        std::string notFound("<html><body><h1>Error 405</h1>Forbidden</body></html>");
        header += std::string("HTTP/1.1 200 OK\r\n");
        header += "Server: " + resp.headers["Server: "] + "\r\n";
        header += "Content-Length: " + std::to_string(notFound.size()) + "\r\n";
        header += std::string("Content-Type: text/html\r\n");
        header += std::string("Connection: close\r\n") + "\r\n";
        header += notFound;
        for (size_t i = 0; i < header.size(); i++)
            respRaw.push_back((std::byte) header[i]);
    }
    ServerLauncher::Instance().getServer(serverCoreId)->send(netInfo.sock, respRaw);
    std::cerr << "RESPONSE SENT!" << std::endl;
#ifdef WIN32
    Sleep(1);
#else
    sleep(1);
#endif
    closesocket(netInfo.sock->socket);
    delete netInfo.sock;
    }
}

HttpHandler::~HttpHandler()
= default;
