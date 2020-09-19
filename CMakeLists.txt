cmake_minimum_required(VERSION 3.0)

project(hsDE)

set(SOURCE 
    ./main.cpp
    ./functions.cpp
    ./de.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCE})