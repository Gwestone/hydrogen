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

# load and link IMGUI
# BEGIN
add_library(imgui
        libs/imgui/imgui.cpp
        libs/imgui/imgui_demo.cpp
        libs/imgui/imgui_draw.cpp
        libs/imgui/imgui_widgets.cpp
        libs/imgui/imgui_tables.cpp
        libs/imgui/backends/imgui_impl_glfw.cpp
        libs/imgui/backends/imgui_impl_opengl3.cpp
        )

# Include directories for ImGui headers
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends)
# END

# Add your source files
add_executable(hydrogen src/main.cpp src/Engine/Shader.cpp src/Engine/Shader.h src/Engine/BuffersArray_AOS.cpp src/Engine/BuffersArray_AOS.h src/Engine/Texture.cpp src/Engine/Texture.h src/Engine/TextureArray.cpp src/Engine/TextureArray.h src/Engine/Camera.cpp src/Engine/Camera.h src/Engine/Timer.cpp src/Engine/Timer.h src/Engine/App.cpp src/Engine/App.h src/Engine/Window.cpp src/Engine/Window.h src/Engine/Mesh.cpp src/Engine/Mesh.h src/Engine/Model.cpp src/Engine/Model.h src/Engine/Vertex.h src/Engine/WindowData.h src/MyApp.h src/Engine/EngineConfig.h src/Engine/include.h src/Engine/Log.cpp src/Engine/Log.h)

# including glad, stb libs in project
add_subdirectory(libs/glad/)
add_subdirectory(libs/stb/)
add_subdirectory(libs/glm/)
add_subdirectory(libs/assimp/)
add_subdirectory(libs/spdlog/)

# Link GLFW and other libraries if needed
target_link_libraries(hydrogen glfw ${OPENGL_LIBRARIES} glad stb glm assimp spdlog imgui)

#post build processes
#build assets folder
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
        )
add_dependencies(hydrogen copy_assets)