project(ZiaTests)

#### PERSONAL INCLUDE
include_directories(../include)

add_subdirectory(GoogletestLibrary)
include_directories(GoogletestLibrary/googlemock/include)

set(TESTS_SOURCES MainGTest.cpp)
set(INCLUDE ../include/Thread/HttpHandler.hpp)
set(SRC ../sources/Thread/HttpHandler.cpp)

add_executable(zia_unit_test ${SRC} ${INCLUDE} ${TESTS_SOURCES})

target_link_libraries(clienttest gtest)