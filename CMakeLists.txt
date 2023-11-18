cmake_minimum_required(VERSION 3.10)
project(escalonador-so)

# All header files
include_directories(include)

# All source files
file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
