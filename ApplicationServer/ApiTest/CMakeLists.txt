cmake_minimum_required(VERSION 3.5)

project(AppServer)

if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

#include(DownloadProject.cmake)
#download_project(PROJ                googletest
#        GIT_REPOSITORY      https://github.com/google/googletest.git
#        GIT_TAG             master
#        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
#        )

#add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -fprofile-arcs -ftest-coverage")

include_directories(../app)

add_executable(apiTests main.cpp)

target_link_libraries(apiTests core)

TARGET_LINK_LIBRARIES(apiTests gtest gtest_main gmock gmock_main )
