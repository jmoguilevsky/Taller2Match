cmake_minimum_required(VERSION 3.5)

project(app)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_definitions(-DMG_ENABLE_THREADS)

set(SOURCE_FILES mongoose-master/mongoose.c src/main.cpp src/ClientHandler.cpp src/utils.cpp src/Server.cpp src/DB.cpp src/DBManager.cpp)

add_executable(app ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(app pthread rocksdb snappy z bz2)