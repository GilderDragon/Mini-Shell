cmake_minimum_required(VERSION 4.0)

project(Mini_Shell C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

set(SOURCES
        src/main.c
        src/builtins.c
        src/executor.c
        src/parser.c
)

add_executable(Mini_Shell ${SOURCES})
