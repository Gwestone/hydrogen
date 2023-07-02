cmake_minimum_required(VERSION 3.12)
project(hydrogen)

# Set C++ version
set(CMAKE_CXX_STANDARD 17)

# Find and link GLFW
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARIES})

# find and link openGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_libraries(${OPENGL_LIBRARIES})

# find and link GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_libraries(${GLUT_LIBRARIES})

#include_directories(${PROJECT_SOURCE_DIR}/libs/glad/include)
# Add your source files
add_executable(hydrogen src/main.cpp src/Shader.cpp src/Shader.h src/BuffersArray_AOS.cpp src/BuffersArray_AOS.h)

# including glad, stb libs in project
add_subdirectory(libs/glad/)
add_subdirectory(libs/stb/)

# Link GLFW and other libraries if needed
target_link_libraries(hydrogen glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glad stb)

#post build processes
#build assets folder
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
        )
add_dependencies(hydrogen copy_assets)