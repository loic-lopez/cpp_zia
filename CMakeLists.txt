cmake_minimum_required(VERSION 3.4)
project(cpp_zia)
set(TARGET_NAME zia)
set(CMAKE_CXX_STANDARD 17)


if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")
elseif (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
elseif (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
    add_library(stdc++fs UNKNOWN IMPORTED)
    if (${CMAKE_SYSTEM} MATCHES "\\.fc[1-9]")
        set_property(TARGET stdc++fs PROPERTY IMPORTED_LOCATION "/usr/lib/gcc/x86_64-redhat-linux/7/libstdc++fs.a")
    else()
        set_property(TARGET stdc++fs PROPERTY IMPORTED_LOCATION "/usr/lib/gcc/x86_64-linux-gnu/7/libstdc++fs.a")
    endif()
endif()

set(SOURCES
        sources/main.cpp
        sources/Thread/HttpHandler.cpp
        sources/Static/ServerConfig.cpp)


set(INCLUDE
        include/Thread/HttpHandler.hpp
        include/Static/ServerConfig.hpp
        include/Static/static_constructor.hpp
        include/api/conf.h
        include/api/http.h
        include/api/module.h
        include/api/net.h
        include/Library/json.hpp



        )


include_directories(include)

add_executable(${TARGET_NAME} ${SOURCES} ${INCLUDE})

add_subdirectory(tests)


