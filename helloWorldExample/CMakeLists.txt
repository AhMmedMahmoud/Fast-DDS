cmake_minimum_required(VERSION 3.20)

project(fastdds_hello_world_example VERSION 1 LANGUAGES CXX)

find_package(Threads REQUIRED)

# User provides this path
set(FAST_DDS_INSTALL_DIR "" CACHE PATH "Fast DDS install directory")

if(NOT FAST_DDS_INSTALL_DIR)
    message(FATAL_ERROR "Please set FAST_DDS_INSTALL_DIR")
endif()

include_directories(
    ${FAST_DDS_INSTALL_DIR}/include
)

link_directories(
    ${FAST_DDS_INSTALL_DIR}/lib
)

file(GLOB HELLO_WORLD_SOURCES_CXX "*.cxx")
file(GLOB HELLO_WORLD_SOURCES_CPP "*.cpp")

add_executable(hello_world ${HELLO_WORLD_SOURCES_CXX} ${HELLO_WORLD_SOURCES_CPP})

target_link_libraries(hello_world fastdds fastcdr Threads::Threads)


