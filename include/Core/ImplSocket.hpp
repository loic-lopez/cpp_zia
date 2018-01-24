//
// Created by Yassir on 24/01/2018.
//

#ifndef CPP_ZIA_IMPLSOCKET_HPP
#define CPP_ZIA_IMPLSOCKET_HPP
#ifdef  _WIN32

#include <winsock.h>

#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#endif

struct ImplSocket {
    int socket;
    struct sockaddr_in server;
};

#endif //CPP_ZIA_IMPLSOCKET_HPP
