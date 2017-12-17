//
// Created by Shae Bolt on 12/16/2017.
//

#ifndef GRIDMAPDISPLAY_WINDOW_H
#define GRIDMAPDISPLAY_WINDOW_H

#include "util.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>


namespace glfwutil {
    class Window;

    using FrameBufferCallback = std::function<void(Window &, int, int)>;
    using MouseCallback = std::function<void(Window &, double, double)>;
    using ScrollCallback = std::function<void(Window &, double, double)>;

    class Window {
        GLFWwindow *m_glfw_window;
        FrameBufferCallback m_frame_buffer_callback;
        MouseCallback m_mouse_callback;
        ScrollCallback m_scroll_callback;
    public:
        Window(int width, int height, const std::string &title, GLFWmonitor *monitor = nullptr,
               GLFWwindow *share = nullptr);

        ~Window();

        int width() const;

        int height() const;

        std::pair<int, int> getSize() const;

        void makeCurrentContext();

        void setFrameBufferCallback(const FrameBufferCallback &callback);

        void setMouseCallback(const MouseCallback &callback);

        void setScrollCallback(const ScrollCallback &callback);

        void setInputMode(int mode, int value);

        void setShouldClose(bool should_close);

        bool shouldClose();

        int getKey(int key);

        void swapBuffers();

        explicit operator GLFWwindow *() const;

    private:

        static void frameBufferCallbackDelegator(GLFWwindow *glfw_window, int width, int height);

        static void mouseCallbackDelegator(GLFWwindow *glfw_window, double xpos, double ypos);

        static void scrollCallbackDelegator(GLFWwindow *glfw_window, double xoffset, double yoffset);
    };
}

#endif //GRIDMAPDISPLAY_WINDOW_H
