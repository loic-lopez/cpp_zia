cmake_minimum_required(VERSION 3.4)
project(cpp_zia)
set(TARGET_NAME zia)
set(CMAKE_CXX_STANDARD 17)


if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs -pthread")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")
elseif (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
elseif (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g")
    add_library(stdc++fs UNKNOWN IMPORTED)
    if (${CMAKE_SYSTEM} MATCHES "\\.fc[1-9]")
        set_property(TARGET stdc++fs PROPERTY IMPORTED_LOCATION "/usr/lib/gcc/x86_64-redhat-linux/7/libstdc++fs.a")
    else ()
        set_property(TARGET stdc++fs PROPERTY IMPORTED_LOCATION "/usr/lib/gcc/x86_64-linux-gnu/7/libstdc++fs.a")
    endif ()
endif ()

SET(MAIN sources/main.cpp)

set(SOURCES
        sources/Handler/HttpHandler.cpp
        sources/Static/ServerConfig.cpp
        sources/Thread/ThreadPool.cpp
        sources/Parser/ReqParser.cpp
        sources/Core/ServerCore.cpp sources/Core/ServerLauncher.cpp sources/Handler/SignalHandler.cpp)

set(INCLUDE
        include/Handler/HttpHandler.hpp
        include/Static/ServerConfig.hpp
        include/Static/static_constructor.hpp
        include/api/conf.h
        include/api/http.h
        include/api/module.h
        include/api/net.h
        include/Library/json.hpp
        include/Core/ServerCore.hpp
        include/Thread/ThreadPool.hpp
        include/Core/ImplSocket.hpp
        include/Core/ServerLauncher.hpp
        include/Parser/ReqParser.hpp include/Enum.hpp

        include/Library/ScanDir.hpp include/Handler/SignalHandler.hpp)

include_directories(include)

add_executable(${TARGET_NAME} ${MAIN} ${SOURCES} ${INCLUDE})
if (UNIX)
    target_link_libraries(${TARGET_NAME} stdc++fs)
endif ()

add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/config $<TARGET_FILE_DIR:${TARGET_NAME}>/config)

add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/html $<TARGET_FILE_DIR:${TARGET_NAME}>/html)


