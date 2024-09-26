cmake_minimum_required(VERSION 3.12)

include_directories(${PROJECT_SOURCE_DIR}/glfw/include/)
include_directories(${PROJECT_SOURCE_DIR}/glad-4.3/include/)

add_subdirectory(glfw)
add_library(glad ${PROJECT_SOURCE_DIR}/glad-4.3/src/glad.c)

add_executable(firstWindow src/firstWindow.cpp)
target_link_libraries(firstWindow glfw glad)
