#include <Core/ServerCore.hpp>
#include "Parser/ReqParser.hpp"
#include <Core/ServerLauncher.hpp>

int main()
{
    ServerLauncher::Instance().launch();

//    std::string httpReq = "GET /hello.txt HTTP/1.1\n";
//    httpReq += "User-Agent: curl/7.16.3 libcurl/7.16.3 OpenSSL/0.9.7l zlib/1.2.3\n";
//    httpReq += "Host: www.example.com\n";
//    httpReq += "Accept-Language: en, mi";
    //ServerCore::Instance().run();
//    ReqParser   parser;
//    parser.parseHttpFormat(httpReq);
    return 0;
}