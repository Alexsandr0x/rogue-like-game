cmake_minimum_required(VERSION 3.8)
project(rogue_like)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Screen.cpp Screen.h Character/Character.cpp Character/Character.h Frame.cpp Frame.h PerlinNoise.cpp PerlinNoise.h Character/Character.cpp Character/Character.cpp Character/MainPlayer.h)
add_executable(rogue_like ${SOURCE_FILES})