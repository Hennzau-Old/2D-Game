#include "game.h"

#include "tile.h"
#include <fstream>

using namespace maths;
using namespace std;

GLuint vao, vbo;

Shader *guiShader;
Texture *texture;

mat4 model;

int n = 0;
int last_n = 0;
int p = 0;

Game::Game()
{
    m_window = new Window("MyPrettyGame", WIDTH, HEIGHT);
    m_mainShader = new Shader("res/shaders/main.vert", "res/shaders/main.frag");

    m_input = new Input(m_window);

    m_camera = new Camera(m_input, m_window);
    m_world = new World();
    m_player = new Player(m_input, m_world);
    m_inventory = new Inventory(m_world);

    texture = new Texture("res/textures/textures.png", GL_RGB);

    model = mat4::translate(0, 0, 0);

    p = m_world->getTypeTile("RED_FLOWER");

    Tile::addTile(&m_vertices, m_window->getWidth() - TILE_SIZE * 2, m_window->getHeight() - TILE_SIZE * 2, 2, 2, maths::vec3::unpack(p), 16, 16);

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

bool line = false;

Game::~Game()
{
    delete m_window;
    delete m_mainShader;
    delete m_input;
    delete m_camera;
    delete m_player;
    delete m_world;
    delete texture;
}

void Game::update()
{
    m_input->update();

    m_player->update();
    m_camera->update(m_player);
    m_world->update();
    m_inventory->update();

    if(m_input->getKeyDown(KEY_F))
        line = !line;

    int x = m_input->getX() / TILE_SIZE;
    int y = m_input->getY() / TILE_SIZE;

    if(m_input->getButtonDown(2))
    {
        if(m_world->getTile(x, y) != 0)
        {
            p = m_world->getTile(x, y);

            Tile::addTile(&m_vertices, m_window->getWidth() - TILE_SIZE * 2, m_window->getHeight() - TILE_SIZE * 2, 2, 2, maths::vec3::unpack(p), 16, 16);

            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(float), &m_vertices[0]);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            m_vertices.clear();
        }
    }

    if(m_input->getButton(1))
    {
        if(m_world->setTile(x, y, p) != 1)
        {
            m_world->getChunkFromTile(x, y)->generateChunk();
            m_world->getChunkFromTile(x, y)->generateBuffers();
        }
    }

    if(m_input->getKeyDown(KEY_E))
    {
        m_inventory->setVisible(!m_inventory->isVisible());
    }
}

void Game::render()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if(line)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    m_window->clearBuffers();

    glDisable(GL_DEPTH_TEST);

    m_mainShader->bind();
    m_mainShader->setUniform("projection", m_camera->getProjectionMatrix());
    m_mainShader->setUniform("view", m_camera->getViewMatrix());
    m_mainShader->setUniform("model", model);

        texture->bind();
            m_world->render();
        texture->unbind();

    m_mainShader->unbind();

    m_player->render(m_mainShader, m_camera);

    m_mainShader->bind();
    m_mainShader->setUniform("projection", m_camera->getProjectionMatrix());
    m_mainShader->setUniform("view", m_camera->getViewMatrix());
    m_mainShader->setUniform("model", model);

        texture->bind();
            m_inventory->render();
        texture->unbind();

    m_mainShader->unbind();

    glEnable(GL_DEPTH_TEST);

    m_window->update();
}
