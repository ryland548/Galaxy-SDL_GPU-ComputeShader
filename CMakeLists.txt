cmake_minimum_required(VERSION 3.20)
project(Triangle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
find_package(glm REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp" main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/inc")
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 glm::glm)
