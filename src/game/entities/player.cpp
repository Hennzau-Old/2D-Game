#include "player.h"
#include "transform.h"
#include "tile.h"
#include "animator.h"
#include "world.h"

using namespace maths;

Animator anim(6, 8, true);

const float playerSize = 1.0f;

Player::Player(Input *input, World *world)
{
    m_input = input;
    m_world = world;
    m_pos = vec2(-1, -1);

    m_texture = new Texture("res/textures/playerSprite.png", GL_RGBA);

    Tile::addTile(&m_vertices, 0, 0, playerSize, playerSize, vec3(0, 0, 0), 6, 4);

    glGenBuffers(1, &m_vbo);
    glGenVertexArrays(1, &m_vao);

    glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 8);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    m_vertices.clear();
}


Player::~Player()
{
    delete m_texture;
}

float dir = 0.0f;
float last_dir = 0.0f;

float xa = 0, ya = 0;
float xDir = 0, yDir = 0;
float speed = 1.0f;

const int t = TILE_SIZE;

int xt = t;
int yt = t;

mat4 modelMatrix;

void Player::updateSprite()
{
    anim.update();
    if(anim.isPlaying())
    {
        Tile::addTile(&m_vertices, 0, 0, playerSize, playerSize, vec3(anim.getCurrentFrame(), dir - 1, 0), 6, 4);

            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(float), &m_vertices[0]);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

        m_vertices.clear();
    }
}

int Player::getSpeed()
{
    return speed;
}

void Player::update()
{
    last_dir = dir;
    anim.pause();

    speed = 1.0f;

    if(m_input->getKeyDown(KEY_F))
        debug_mode = !debug_mode;

    if(m_input->getKey(KEY_Q))
        speed = 2.0f;
    if(m_input->getKey(KEY_W) && yDir == 0 && xDir == 0)
    {
        yDir = -speed;
        dir = 2;
    }
    if(m_input->getKey(KEY_S) && yDir == 0 && xDir == 0)
    {
        yDir = speed;
        dir = 3;
    }
    if(m_input->getKey(KEY_A) && xDir == 0 && yDir == 0)
    {
        xDir = -speed;
        dir = 1;
    }
    if(m_input->getKey(KEY_D) && xDir == 0 && yDir == 0)
    {
        xDir = speed;
        dir = 4;
    }

    if(xa != 0 && xt > 0)
    {
        move(xa, 0);
        xt--;
        anim.play();

        if(xt <= 0)
        {
            xDir = 0;
            xt = t;
        }
    }

    if(ya != 0 && yt > 0)
    {
        move(0, ya);
        yt--;
        anim.play();

        if(yt <= 0)
        {
            yDir = 0;
            yt = t;
        }
    }

    xa = xDir;
    ya = yDir;

    updateSprite();

    modelMatrix = mat4::translate(m_pos.x, m_pos.y, 0);
}

void Player::render(Shader *shader, Camera *camera)
{
    shader->bind();
    shader->setUniform("projection", camera->getProjectionMatrix());
    shader->setUniform("view", camera->getViewMatrix());
    shader->setUniform("model", modelMatrix);

    m_texture->bind();
        glBindVertexArray(m_vao);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    m_texture->unbind();

    shader->unbind();
}


void Player::move(float xa, float ya)
{
    if(!isColliding(xa, 0)) m_pos.x += xa;
    if(!isColliding(0, ya)) m_pos.y += ya;
}

bool Player::isColliding(float xa, float ya)
{
    float s = playerSize * TILE_SIZE;

    int x0 = (int) (m_pos.x + xa + 1) / TILE_SIZE;
    int x1 = (int) (m_pos.x + xa + s) / TILE_SIZE;

    int y0 = (int) (m_pos.y + ya + 1) / TILE_SIZE;
    int y1 = (int) (m_pos.y + ya + s) / TILE_SIZE;

    if(vec3::unpack(m_world->getTile(x0, y0)).z == 1) return true;
    if(vec3::unpack(m_world->getTile(x1, y0)).z == 1) return true;
    if(vec3::unpack(m_world->getTile(x0, y1)).z == 1) return true;
    if(vec3::unpack(m_world->getTile(x1, y1)).z == 1) return true;

    return false;
}
