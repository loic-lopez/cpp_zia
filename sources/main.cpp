#include <Core/ServerCore.hpp>

int main()
{
    ServerCore::Instance().run([](zia::api::Net::Raw rawData, zia::api::NetInfo netInfo)
                               {
                                   ThreadPool::Instance().addThread(rawData, netInfo);
                               });

    return 0;
}