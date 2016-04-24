cmake_minimum_required(VERSION 3.5)

project(AppServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_definitions(-DMG_ENABLE_THREADS)

file(GLOB Mongoose_SRC
        "src/*.cpp"
        "src/mongoose-master/*.c"
        )

set(SOURCE_FILES ${Mongoose_SRC} src/DB/LoginDB.cpp src/DB/LoginDB.h src/HTTPResponse.cpp src/HTTPResponse.h src/Handlers/SignUp.cpp src/Handlers/SignUp.h src/DB/MatchesDB.cpp src/DB/MatchesDB.h src/DB/ChatDB.cpp src/DB/ChatDB.h)

add_executable(app ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(app pthread rocksdb snappy z bz2)