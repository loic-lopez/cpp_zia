#include <Thread/HttpHandler.hpp>
#include <iostream>

int main()
{

    HttpHandler httpHandler([] () {
        std::cerr << "THREAD" << std::endl;
    });

    return 0;
}