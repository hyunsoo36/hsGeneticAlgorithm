cmake_minimum_required(VERSION 3.0)

project(hello)

set(SOURCE 
    ./hsGeneticAlgorithm/main.cpp
    ./hsGeneticAlgorithm/functions.cpp
    ./hsGeneticAlgorithm/de.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCE})