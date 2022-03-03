cmake_minimum_required(VERSION 3.15)

project(BlockChain)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE release)

add_executable(BlockChain Block.cpp BlockChain.cpp sha256.cpp main.cpp)
