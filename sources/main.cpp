#include <Core/ServerCore.hpp>

int main()
{
    ServerCore &serverCore = ServerCore::Instance();

    serverCore.config(zia::api::Conf());
    ServerCore::Instance().run([](zia::api::Net::Raw rawData, zia::api::NetInfo netInfo)
                               {
                                   ThreadPool::Instance().addThread(std::move(rawData), std::move(netInfo));
                               });


    return 0;
}