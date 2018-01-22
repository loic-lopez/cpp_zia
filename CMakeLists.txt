cmake_minimum_required(VERSION 3.4)
project(cpp_zia)
set(TARGET_NAME zia)
set(CMAKE_CXX_STANDARD 17)


#Google tests
#enable_testing()
#include( CTest )
#add_subdirectory(test)


set(SOURCES sources/main.cpp
        sources/Thread/HttpHandler.cpp)


set(INCLUDE include/Thread/HttpHandler.hpp)

include_directories(include)

add_executable(${TARGET_NAME} ${SOURCES} ${INCLUDE})

add_subdirectory(tests)

