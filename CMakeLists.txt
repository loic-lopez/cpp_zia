cmake_minimum_required(VERSION 3.4)
project(cpp_zia)
set(TARGET_NAME zia)
set(CMAKE_CXX_STANDARD 17)


if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")
endif()

#Google tests
#enable_testing()
#include( CTest )
#add_subdirectory(test)


set(SOURCES sources/main.cpp
        sources/Thread/HttpHandler.cpp sources/Static/ServerConfig.cpp)


set(INCLUDE include/Thread/HttpHandler.hpp include/Static/ServerConfig.hpp include/Static/static_constructor.hpp)

include_directories(include)

add_executable(${TARGET_NAME} ${SOURCES} ${INCLUDE})

add_subdirectory(tests)


