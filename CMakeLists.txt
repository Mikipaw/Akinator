cmake_minimum_required(VERSION 3.20)
project(Akinator)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        main.cpp
        src/Akinator.cpp
        src/Interface.cpp
        src/mystr.cpp
        )

add_executable(Akinator ${SOURCE_FILES})

target_include_directories(Akinator PUBLIC headers)