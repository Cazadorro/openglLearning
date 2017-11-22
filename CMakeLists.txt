cmake_minimum_required(VERSION 3.8)
project(GridMapDisplay)

set(CMAKE_CXX_STANDARD 14)


#add_library(GLAD "glad.c")
#set(LIBS ${LIBS} GLAD dl)
include_directories("include")
set(SOURCE_FILES main.cpp include/glad/glad.h glad.c glutil/camera.cpp glutil/camera.h glutil/ShaderProgram.cpp glutil/ShaderProgram.h glutil/Shader.cpp glutil/Shader.h glutil/ioutil.cpp glutil/ioutil.h glutil/UniformVariable.cpp glutil/UniformVariable.h glutil/geometry.cpp glutil/geometry.h glutil/RawImage.cpp glutil/RawImage.h glutil/Texture2D.cpp glutil/Texture2D.h glutil/stbi_image_imp.h glutil/VertexBufferObject.cpp glutil/VertexBufferObject.h)

#find_package(GLFW3 REQUIRED)
#message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
add_executable(GridMapDisplay ${SOURCE_FILES})
#-lglfw3

target_link_libraries(GridMapDisplay glfw3 rt m dl Xrandr Xinerama Xxf86vm Xext Xcursor Xrender Xfixes X11 pthread xcb Xau Xdmcp GL Xi )


target_link_libraries(GridMapDisplay ${LIBS})