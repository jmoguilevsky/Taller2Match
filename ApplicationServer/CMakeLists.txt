cmake_minimum_required(VERSION 3.5)

project(AppServer)

add_subdirectory(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_definitions(-DMG_ENABLE_THREADS)

file(GLOB app_src
        "src/*.cpp"
        "src/DB/*.cpp"
        "src/Handlers/*.cpp"
        "src/mongoose-master/*.c"
        )

set(SOURCE_FILES ${app_src} src/mongoose-master/MongooseConnectionManager.cpp src/mongoose-master/MongooseConnectionManager.h src/HandlerSelector.cpp src/HandlerSelector.h)

add_library(core ${SOURCE_FILES})

add_executable(app main.cpp)

target_link_libraries(app core)

target_link_libraries(app pthread rocksdb snappy z bz2)
