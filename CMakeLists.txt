cmake_minimum_required(VERSION 3.0)

project(lab5)

add_executable(lab5 src/main.cpp)

install(TARGETS lab5 RUNTIME DESTINATION bin)
