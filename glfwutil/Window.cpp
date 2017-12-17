//
// Created by Shae Bolt on 12/16/2017.
//

#include "Window.h"
#include <exception>

glfwutil::Window::Window(int width, int height, const std::string &title, GLFWmonitor *monitor, GLFWwindow *share) {
    m_glfw_window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
    if (m_glfw_window == nullptr) {
        throw (std::runtime_error("Failed to create GLFW window"));
    }
    glfwSetWindowUserPointer(m_glfw_window, this);
}

glfwutil::Window::~Window() {
    glfwDestroyWindow(m_glfw_window);
}

int glfwutil::Window::width() const {
    int width;
    glfwGetWindowSize(m_glfw_window, &width, nullptr);
    return width;
}

int glfwutil::Window::height() const {
    int height;
    glfwGetWindowSize(m_glfw_window, nullptr, &height);
    return height;
}

std::pair<int, int> glfwutil::Window::getSize() const {
    int width;
    int height;
    glfwGetWindowSize(m_glfw_window, &width, &height);
    return std::make_pair(width, height);
}

void glfwutil::Window::makeCurrentContext() {
    glfwMakeContextCurrent(m_glfw_window);
}

void glfwutil::Window::setFrameBufferCallback(const FrameBufferCallback &callback) {
    m_frame_buffer_callback = callback;
    glfwSetFramebufferSizeCallback(m_glfw_window, frameBufferCallbackDelegator);
}

void glfwutil::Window::setMouseCallback(const MouseCallback &callback) {
    m_mouse_callback = callback;
    glfwSetCursorPosCallback(m_glfw_window, mouseCallbackDelegator);
}

void glfwutil::Window::setScrollCallback(const ScrollCallback &callback) {
    m_scroll_callback = callback;
    glfwSetScrollCallback(m_glfw_window, scrollCallbackDelegator);
}

void glfwutil::Window::setInputMode(int mode, int value) {
    glfwSetInputMode(m_glfw_window, mode, value);
}

glfwutil::Window::operator GLFWwindow *() const {
    return m_glfw_window;
}

void glfwutil::Window::frameBufferCallbackDelegator(GLFWwindow *glfw_window, int width, int height) {
    auto obj_ptr = static_cast<Window *>(glfwGetWindowUserPointer(glfw_window));
    obj_ptr->m_frame_buffer_callback(*obj_ptr, width, height);
}

void glfwutil::Window::mouseCallbackDelegator(GLFWwindow *glfw_window, double xpos, double ypos) {
    auto obj_ptr = static_cast<Window *>(glfwGetWindowUserPointer(glfw_window));
    obj_ptr->m_mouse_callback(*obj_ptr, xpos, ypos);
}

void glfwutil::Window::scrollCallbackDelegator(GLFWwindow *glfw_window, double xoffset, double yoffset) {
    auto obj_ptr = static_cast<Window *>(glfwGetWindowUserPointer(glfw_window));
    obj_ptr->m_scroll_callback(*obj_ptr, xoffset, yoffset);
}

void glfwutil::Window::setShouldClose(bool should_close) {
    glfwSetWindowShouldClose(m_glfw_window, should_close);
}

int glfwutil::Window::getKey(int key) {
    return glfwGetKey(m_glfw_window, key);
}

bool glfwutil::Window::shouldClose() {
    return static_cast<bool>(glfwWindowShouldClose(m_glfw_window));
}

void glfwutil::Window::swapBuffers() {
    glfwSwapBuffers(m_glfw_window);
}
