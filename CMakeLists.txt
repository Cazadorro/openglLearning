cmake_minimum_required(VERSION 3.8)
project(GridMapDisplay)

set(CMAKE_CXX_STANDARD 14)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

#add_library(GLAD "glad.c")
#set(LIBS ${LIBS} GLAD dl)
configure_file(cmake_configuration/root_directory.h.in configuration/root_directory.h)

set(SOURCE_FILES main.cpp include/glad/glad.h glad.c glutil/camera.cpp glutil/camera.h glutil/ShaderProgram.cpp glutil/ShaderProgram.h glutil/Shader.cpp glutil/Shader.h glutil/ioutil.cpp glutil/ioutil.h glutil/UniformVariable.cpp glutil/UniformVariable.h glutil/geometry.cpp glutil/geometry.h glutil/Image.cpp glutil/Image.h glutil/Texture2D.cpp glutil/Texture2D.h glutil/stbi_image_imp.h glutil/VertexBufferObject.cpp glutil/VertexBufferObject.h glutil/VertexAttributeLocation.cpp glutil/VertexAttributeLocation.h glutil/VertexAttributeObject.cpp glutil/VertexAttributeObject.h glutil/resourceio.h cmake_configuration/root_directory.h.in glutil/FileSystem.cpp glutil/FileSystem.h glfwutil/util.cpp glfwutil/util.h glutil.h glfwutil.h glfwutil/Window.cpp glfwutil/Window.h)
include_directories("include/")
#include_directories("glm_includes/")
include_directories(${CMAKE_BINARY_DIR}/configuration)
#find_package(GLFW3 REQUIRED)
#message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
#-lglfw3


if(LINUX)
    message("using linux link targets")
    target_link_libraries(${PROJECT_NAME} glfw3 rt m dl Xrandr Xinerama Xxf86vm Xext Xcursor Xrender Xfixes X11 pthread xcb Xau Xdmcp GL Xi )
elseif(WIN32)
#    find_package(GLFW3 REQUIRED)
#    message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
    message("using windows link targets")
    target_link_libraries(${PROJECT_NAME} -lglfw3 -lopengl32)
endif()
