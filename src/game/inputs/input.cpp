#include "input.h"

float lx = 0, ly = 0;
float cx = 0, cy = 0;

bool contains(std::vector<int> v, int x);

float dsx, dsy;

float offset;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    dsx += xoffset;
    dsy += yoffset;

    offset = xoffset + yoffset;
}

Input::Input(Window *window)
{
    m_window = window;

    glfwSetScrollCallback(window->getWindow(), scroll_callback);
}


Input::~Input()
{

}

void Input::update()
{
    mouseMove = false;

    if(isGrabed())
        glfwSetInputMode(m_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(m_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glfwGetCursorPos(m_window->getWindow(), &x, &y);

    if(lx != x || ly != y)
    {
        mouseMove = true;
    }

    cx = x - lx;
    dx = cx;
    lx = x;

    cy = y - ly;
    dy = cy;
    ly = y;

    keysDown.clear();
    for(int i = 0; i < NUM_KEY; i++)
    {
        if(getKey(i) && !contains(keys, i))
        {
          keysDown.push_back(i);
        }
    }

    keys.clear();
    for(int i = 0; i < NUM_KEY; i++)
    {
        if(getKey(i))
          keys.push_back(i);
    }

    mouseDown.clear();
    for(int i = 0; i < 5; i++)
    {
        if(getButton(i) && !contains(mouse, i))
            mouseDown.push_back(i);
    }

    mouse.clear();
    for(int i = 0; i < 5; i++)
    {
        if(getButton(i))
            mouse.push_back(i);
    }
}

bool Input::getKey(int key)
{
  return (glfwGetKey(m_window->getWindow(), key));
}

bool Input::getKeyDown(int key)
{
  return contains(keysDown, key);
}

bool Input::getButton(int button)
{
  return (glfwGetMouseButton(m_window->getWindow(), button));
}

bool Input::getButtonDown(int button)
{
  return contains(mouseDown, button);
}

bool contains(std::vector<int> v, int x)
{
      if (v.empty())
           return false;
      if (find(v.begin(), v.end(), x) != v.end())
           return true;
      else
           return false;
}

float Input::getDWheel()
{
    return (dsy + dsx) / 2.0f;
}

float Input::getDs()
{
    return offset;
}
