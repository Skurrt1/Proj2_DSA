cmake_minimum_required(VERSION 3.14)
project(TopBilled CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

file(GLOB SOURCES src/*.cpp)
add_executable(top_billed ${SOURCES})
target_include_directories(top_billed PRIVATE include)
