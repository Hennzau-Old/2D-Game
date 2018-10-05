#include "window.h"

Window::Window(const char* title, int width, int height)
{
    m_title = title;
    m_width = width;
    m_height = height;

    if(!glfwInit())
    {
        printf("Failed to init GLFW ! ");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

    if(!m_window)
    {
        printf("Failed to create the window ! ");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);
    glewExperimental = true;

    if(glewInit() != GLEW_OK)
    {
        printf("Failed to init GLEW ! ");
        return;
    }

    glfwSwapInterval(0);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

Window::~Window()
{

}

void Window::update()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
    glfwGetWindowSize(m_window, &m_width, &m_height);
}

void Window::clearBuffers()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::destroy()
{
    glfwTerminate();
}

bool Window::wasResized()
{
    if(m_lastWidth != m_width || m_lastHeight != m_height)
    {
        m_lastWidth = m_width;
        m_lastHeight = m_height;

        return true;
    }

    return false;
}

bool Window::isClosed()
{
    return glfwWindowShouldClose(m_window);
}

float Window::getAspect()
{
    return (float) m_width / (float) m_height;
}
