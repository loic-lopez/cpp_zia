//
// Created by loic lopez on 06/02/2018.
//

#define UNIT_TEST

#include <gtest/gtest.h>
#include <Core/ImplSocket.hpp>
#include <Static/ServerConfig.hpp>

TEST(ServerConfigTest, WebSiteConfs)
{
    ASSERT_TRUE(!ServerConfig::WebSiteConfs.empty());
}

TEST(ServerConfigTest, isConfigFileExists)
{
    ASSERT_FALSE(ServerConfig::isConfigFileExists("unittests"));
    ASSERT_TRUE(ServerConfig::isConfigFileExists("CMakeFiles"));
}

TEST(ServerConfigTest, LoadDefaultWebSiteConf)
{
    ServerConfig::LoadDefaultWebSiteConf();
    ASSERT_TRUE(std::get<std::string>(ServerConfig::WebSiteConfs[0]["document_root"].v) == "html/");
}

TEST(ServerConfigTest, FormatIPAddress)
{
    std::shared_ptr<zia::api::ImplSocket> socket;
    socket = std::shared_ptr<zia::api::ImplSocket>(new zia::api::ImplSocket(0));
    struct sockaddr sockaddr1{};
    sockaddr1 = ServerConfig::FormatIPAddress(socket->sockaddr, 80, "localhost");
    ASSERT_TRUE(sizeof(sockaddr1) == sizeof(struct sockaddr));
}