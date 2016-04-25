cmake_minimum_required(VERSION 3.5)

project(AppServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_definitions(-DMG_ENABLE_THREADS)

file(GLOB Mongoose_SRC
        "src/*.cpp"
        "src/DB/*.cpp"
        "src/Handlers/*.cpp"
        "src/mongoose-master/*.c"
        )

set(SOURCE_FILES ${Mongoose_SRC})

add_executable(app ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(app pthread rocksdb snappy z bz2)