//
// Created by loic lopez on 06/02/2018.
//

#define UNIT_TEST

#include <gtest/gtest.h>
#include <Static/ServerConfig.hpp>

TEST(ServerConfigTest, WebSiteConfs)
{
    ASSERT_TRUE(!ServerConfig::WebSiteConfs.empty());
}

TEST(ServerConfigTest, isConfigFileExists)
{
    ASSERT_FALSE(ServerConfig::isConfigFileExists("unittests"));

    //ASSERT_TRUE(ServerConfig::isConfigFileExists("GoogletestLibrary"));
}