//
// Created by Yassir on 24/01/2018.
//

#ifndef CPP_ZIA_IMPLSOCKET_HPP
#define CPP_ZIA_IMPLSOCKET_HPP

#ifdef WIN32

#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
#endif

namespace zia::api
{
    struct ImplSocket {
#ifdef WIN32
        SOCKET socket;
#else
        int socket;
#endif
        struct sockaddr_in sockaddr;

        explicit ImplSocket(int socket) : sockaddr({0})
        {
            this->socket = socket;
        };
        ImplSocket() = default;
    };

}
#endif //CPP_ZIA_IMPLSOCKET_HPP
