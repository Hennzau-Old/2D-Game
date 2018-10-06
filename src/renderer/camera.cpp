#include "camera.h"

using namespace maths;

Camera::Camera(Input *input, Window *window)
{
    m_input = input;
    m_window = window;

    setOrthographic(-1.0f, 10.0f);

    m_projection = mat4::orthographic(window->getWidth(), 0, 0, window->getHeight(), m_znear, m_zfar);
    m_view = mat4::identity();
}

Camera::~Camera()
{

}

float sensitivity = 2;

void Camera::update(Player *player)
{
    if(m_window->wasResized())
    {
        m_projection = mat4::orthographic(m_window->getWidth(), 0, 0, m_window->getHeight(), m_znear, m_zfar);
        glViewport(0, 0, m_window->getWidth(), m_window->getHeight());
    }

    m_transform = Transform();
    m_transform.setPosition(vec3(m_pos.copy().negate().x, m_pos.copy().negate().y, 0));

    m_view = m_transform.toMatrix();
}

void Camera::setOrthographic(float znear, float zfar)
{
    m_znear = znear;
    m_zfar = zfar;
}

void Camera::move(float xa, float ya)
{
    m_pos.x += xa;
    m_pos.y += ya;
}
