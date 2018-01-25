#include <Core/ServerCore.hpp>

int main()
{
    ServerCore serverCore;

    serverCore.config(zia::api::Conf());
    serverCore.run([&serverCore](zia::api::Net::Raw rawData, zia::api::NetInfo netInfo)
                               {
                                   serverCore.getThreadPool().addThread(std::move(rawData), std::move(netInfo));
                               });


    return 0;
}