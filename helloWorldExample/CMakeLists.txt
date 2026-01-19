cmake_minimum_required(VERSION 3.20)

project(fastdds_hello_world_example VERSION 1 LANGUAGES CXX)

find_package(Threads REQUIRED)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../install/include
)

link_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../install/lib
)

file(GLOB HELLO_WORLD_SOURCES_CXX "*.cxx")
file(GLOB HELLO_WORLD_SOURCES_CPP "*.cpp")

add_executable(hello_world ${HELLO_WORLD_SOURCES_CXX} ${HELLO_WORLD_SOURCES_CPP})

target_link_libraries(hello_world fastdds fastcdr Threads::Threads)


