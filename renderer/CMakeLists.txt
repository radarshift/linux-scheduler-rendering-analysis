cmake_minimum_required(VERSION 3.10)
project(analysisrenderer)

# set up standard
set(CMAKE_CXX_STANDARD 17)

# add glfw (built from source)
add_subdirectory(dependencies/glfw)

# add GLAD
add_library(glad dependencies/glad/glad.c)
target_include_directories(glad PUBLIC dependencies/glad/include)

# create executable
add_executable(rndr src/main.cpp)

# links
target_link_libraries(rndr PRIVATE glfw glad)

if(UNIX AND NOT APPLE)
    find_package(OpenGL REQUIRED)
    target_link_libraries(rndr PRIVATE OpenGL::GL)
endif()
