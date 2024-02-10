cmake_minimum_required(VERSION 3.5...3.21 FATAL_ERROR)
project(mvcgui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/third-party)

include_directories(${THIRD_PARTY_DIR})
include_directories(${THIRD_PARTY_DIR}/imgui)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/mvcgui)

add_library(mvcgui STATIC)

target_sources(mvcgui PRIVATE 
    mvcgui/core/object_p.h
    mvcgui/core/object_p_p.h
    mvcgui/core/object.cpp)
