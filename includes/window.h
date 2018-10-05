#ifndef WINDOW
#define WINDOW

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

class Window
{
    public:
        Window(const char* title, int width, int height);
        ~Window();

        void          update();
        void          clearBuffers();
        void          destroy();

        int           getWidth() { return m_width; }
        int           getHeight() { return m_height; }

        float         getAspect();

        const char*   getTitle() { return m_title; }

        bool          wasResized();
        bool          isClosed();

        GLFWwindow*   getWindow() { return m_window; }

    private:
        int           m_width,
                      m_height,
                      m_lastWidth,
                      m_lastHeight;

        const char*   m_title;
        GLFWwindow*   m_window;
};

#endif
