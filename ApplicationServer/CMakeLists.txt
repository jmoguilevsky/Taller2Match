cmake_minimum_required(VERSION 3.5)

project(AppServer)

add_subdirectory(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_definitions(-DMG_ENABLE_THREADS)

file(GLOB app_src
        "src/*.cpp"
        "src/DB/*.cpp"
        "src/Handlers/*.cpp"
        "src/HTTP/*.cpp"
        "src/mongoose-master/*.c*"
        )

set(SOURCE_FILES ${app_src} src/Handlers/Chat.cpp src/Handlers/Chat.h src/Handlers/Notification.cpp src/Handlers/Notification.h)

add_library(core ${SOURCE_FILES})

add_executable(app main.cpp src/Handlers/MatchHandlerSelector.cpp src/Handlers/MatchHandlerSelector.h)

target_link_libraries(app core)

target_link_libraries(app pthread rocksdb snappy z bz2)
