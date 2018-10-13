#include "camera.h"
#include "world.h"
#include "game.h"

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

    int x = player->getX();
    int y = player->getY();

//    m_pos.x = x - m_window->getWidth() / 2;
//    m_pos.y = y - m_window->getHeight() / 2;

    if(x >= m_pos.x + (m_window->getWidth() / 3 * 2)) m_pos.x += (player->getSpeed());
    if(x <= m_pos.x + (m_window->getWidth() / 3)) m_pos.x -= (player->getSpeed());
    if(y <= m_pos.y + (m_window->getHeight() / 3 * 2)) m_pos.y -= (player->getSpeed());
    if(y >= m_pos.y + (m_window->getHeight() / 3)) m_pos.y += (player->getSpeed());

    if(m_pos.x < 0) m_pos.x = 0;
    if(m_pos.x > WORLD_SIZE * CHUNK_SIZE * TILE_SIZE - WIDTH) m_pos.x = WORLD_SIZE * CHUNK_SIZE * TILE_SIZE - WIDTH;

    if(m_pos.y < 0) m_pos.y = 0;
    if(m_pos.y > WORLD_SIZE * CHUNK_SIZE * TILE_SIZE - HEIGHT) m_pos.y = WORLD_SIZE * CHUNK_SIZE * TILE_SIZE - HEIGHT;


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
