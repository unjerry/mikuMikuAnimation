cmake_minimum_required(VERSION 3.12)
project(mikuMikuAnimation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

configure_file(${PROJECT_SOURCE_DIR}/include/learnopengl/root_directory.h.in ${PROJECT_SOURCE_DIR}/include/learnopengl/root_directory.h)

include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PROJECT_SOURCE_DIR}/glfw/include/)
include_directories(${PROJECT_SOURCE_DIR}/glad-4.3/include/)
include_directories(${PROJECT_SOURCE_DIR}/glm/)

file(COPY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${PROJECT_BINARY_DIR})

add_subdirectory(glfw)
add_library(glad ${PROJECT_SOURCE_DIR}/glad-4.3/src/glad.c)

add_executable(firstWindow src/firstWindow.cpp)
target_link_libraries(firstWindow glfw glad)

add_executable(basicFinal src/basicFinal.cpp)
target_link_libraries(basicFinal glfw glad)
