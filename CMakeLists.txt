cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME openscrapelib)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
set(LIB_TYPE SHARED)

add_compile_definitions(YEUX_V2_EXPORTS)

include_directories(include)

file(GLOB SRC_FILES "src/*.cpp" "src/CTablemap/*.cpp" "src/CTransform/*.cpp" "src/CTransform/hash/*.cpp" "src/CTransform/pdiff/*.cpp")
file(GLOB HEA_FILES "include/*.hpp" "include/CCritSec/*.hpp" "include/CTablemap/*.hpp" "include/CTransform/*.hpp" "include/CTransform/hash/*.cpp" "include/CTransform/pdiff/*.cpp")

add_library(${PROJECT_NAME} ${LIB_TYPE} ${SRC_FILES} ${HEA_FILES})

message(STATUS "HEADERS: ${HEA_FILES}")
