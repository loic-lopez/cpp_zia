project(ZiaTests)

#### PERSONAL INCLUDE
include_directories(../include)

set(CMAKE_AUTOMOC ON)

if (MSVC)
    foreach (flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if (${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif (${flag_var} MATCHES "/MD")
        if (${flag_var} MATCHES "/MDd")
            string(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
        endif (${flag_var} MATCHES "/MDd")
    endforeach (flag_var)
endif (MSVC)

add_subdirectory(GoogletestLibrary)
include_directories(GoogletestLibrary/googlemock/include)

set(TESTS_SOURCES TestSources/HttpHandlerTest.cpp)
file(GLOB INCLUDE ${PROJECT_SOURCE_DIR}/include/*.hpp ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB INCLUDE ${PROJECT_SOURCE_DIR}/sources/*.cpp)

add_executable(ZiaTests ${SRC} ${INCLUDE} ${TESTS_SOURCES})

target_link_libraries(ZiaTests gtest_main)