project(ZiaTests)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/tests/externals/" ${CMAKE_MODULE_PATH})

include(CodeCoverage)
APPEND_COVERAGE_COMPILER_FLAGS()

set(COVERAGE_EXCLUDES '${CMAKE_SOURCE_DIR}/tests')

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

set(TESTS_SOURCES TestSources/HttpHandlerTest.cpp TestSources/ServerConfigTest.cpp)
SET(COVERAGE_SOURCES ${SRC} ${SOURCES} ${INCLUDES} ${TESTS_SOURCES})

SETUP_TARGET_FOR_COVERAGE(ZiaTests_coverage ZiaTests html_zia_coverage
        # Name for custom target.
        #				test_driver         # Name of the test driver executable that runs the tests.
        #									# NOTE! This should always have a ZERO as exit code
        #									# otherwise the coverage generation will not complete.
        #				coverage            # Name of output directory.
        )

add_executable(ZiaTests ${SRC} ${SOURCES} ${INCLUDES} ${TESTS_SOURCES})

target_link_libraries(ZiaTests gtest_main)
