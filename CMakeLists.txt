cmake_minimum_required(VERSION 3.0)

project(lab5)

set (CMAKE_OBJCXX_STANDARD 17)

add_executable(lab5 src/main.cpp src/lib/mainClass.cpp src/lib/subClass.cpp)

install(TARGETS lab5 RUNTIME DESTINATION bin)
