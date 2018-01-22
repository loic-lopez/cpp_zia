project(ZiaTests)

#### PERSONAL INCLUDE
include_directories(../include)

add_subdirectory(GoogletestLibrary)
include_directories(GoogletestLibrary/googlemock/include)

set(TESTS_SOURCES TestSources/HttpHandlerTest.cpp)
set(INCLUDE ../include/Thread/HttpHandler.hpp)
set(SRC ../sources/Thread/HttpHandler.cpp)

add_executable(ZiaTests ${SRC} ${INCLUDE} ${TESTS_SOURCES})

target_link_libraries(ZiaTests gtest_main)