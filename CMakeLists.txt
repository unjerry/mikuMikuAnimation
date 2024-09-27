cmake_minimum_required(VERSION 3.12)
project(mikuMikuAnimation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

# art resource path
configure_file(${PROJECT_SOURCE_DIR}/include/learnopengl/root_directory.h.in ${PROJECT_SOURCE_DIR}/include/learnopengl/root_directory.h)

# include path
include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PROJECT_SOURCE_DIR}/glfw/include/)
include_directories(${PROJECT_SOURCE_DIR}/glm/)
include_directories(${PROJECT_SOURCE_DIR}/polyscope/include)

# build binarys
add_subdirectory(glfw)

set(GLAD_SOURCES_DIR "${PROJECT_SOURCE_DIR}/glad")
add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)
glad_add_library(gl REPRODUCIBLE MX API gl:core=4.3)

add_subdirectory(polyscope)


# build executable
add_executable(firstWindow src/firstWindow.cpp)
target_link_libraries(firstWindow gl glfw)

add_executable(basicFinal src/basicFinal.cpp)
target_link_libraries(basicFinal gl glfw)

add_executable(multiwin_mx src/multiwin_mx.cpp)
target_link_libraries(multiwin_mx gl glfw)

add_executable (polscoTest src/polscoTest.cpp)
target_link_libraries(polscoTest polyscope)

