cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME openscrapelib)
project(${PROJECT_NAME})

###################################################################################################
# Configure conan
if(NOT EXISTS ${CMAKE_BINARY_DIR}/conan.cmake)
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(
  REQUIRES
    gtest/1.8.1@bincrafters/stable
  BASIC_SETUP CMAKE_TARGETS
  BUILD missing
  OPTIONS
    gtest:shared=False
)
###################################################################################################

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
set(LIB_TYPE SHARED)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

add_compile_definitions(YEUX_V2_API)

include_directories(include)

file(GLOB SRC_FILES "src/*.cpp" "src/CTablemap/*.cpp" "src/CTransform/*.cpp" "src/CTransform/hash/*.cpp" "src/CTransform/pdiff/*.cpp")
file(GLOB HEA_FILES "include/*.hpp" "include/CCritSec/*.hpp" "include/CTablemap/*.hpp" "include/CTransform/*.hpp" "include/CTransform/hash/*.cpp" "include/CTransform/pdiff/*.cpp")

add_library(${PROJECT_NAME} ${LIB_TYPE} ${SRC_FILES} ${HEA_FILES})

message(STATUS "HEADERS: ${HEA_FILES}")

###################################################################################################
# Test
enable_testing()

file(GLOB TEST_SOURCES "test/*.cpp")

add_executable(all_tests
  ${TEST_SOURCES}
)

target_link_libraries(all_tests
  PRIVATE
    CONAN_PKG::gtest
    ${PROJECT_NAME}
)

add_test(all_tests all_tests)
###################################################################################################