cmake_minimum_required(VERSION 3.20)

project(game CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH C:/msys64/ucrt64)

find_package(raylib CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    C:/msys64/ucrt64/include
    include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
)