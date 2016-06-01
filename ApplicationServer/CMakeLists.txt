cmake_minimum_required(VERSION 3.5)

project(AppServer)

add_subdirectory(test)

add_subdirectory(ApiTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -fprofile-arcs -ftest-coverage" )

add_definitions(-DMG_ENABLE_THREADS)

file(GLOB app_src
        "src/*.cpp"
        "src/DB/*.cpp"
        "src/Handlers/*.cpp"
        "src/HandlersHTTP/*.cpp"
        "src/HTTP/*.cpp"
        "src/Mongoose/*"
        "src/Mongoose/mongoose-master/*"
        )

set(SOURCE_FILES ${app_src})

add_library(core ${SOURCE_FILES})

add_executable(app main.cpp)

target_link_libraries(app core)

target_link_libraries(app pthread rocksdb snappy z bz2 gtest gtest_main rt)
