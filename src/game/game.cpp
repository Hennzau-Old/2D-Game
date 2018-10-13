#include "game.h"

#include "tile.h"
#include <fstream>

using namespace maths;
using namespace std;

GLuint vao, vbo;

Shader *guiShader;
Texture *texture;

mat4 model;

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
    m_inventory->update(m_input);

    if(m_input->getKeyDown(KEY_F))
        line = !line;

    int x = (m_input->getX() + m_camera->getX()) / TILE_SIZE;
    int y = (m_input->getY() + m_camera->getY()) / TILE_SIZE;

    if(m_input->getButtonDown(2))
    {
        if(m_world->getTile(x, y) != 0)
        {
            m_inventory->setItem(m_world->getTile(x, y));
        }
    }

    if(m_input->getButton(1))
    {
        if(m_world->setTile(x, y, m_inventory->getSelectedItem()) != 1)
        {
            m_world->getChunkFromTile(x, y)->generateChunk();
            m_world->getChunkFromTile(x, y)->updateBuffers();
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
            m_world->render(m_camera);
        texture->unbind();

    m_mainShader->unbind();

    m_player->render(m_mainShader, m_camera);

    m_mainShader->bind();
    m_mainShader->setUniform("projection", m_camera->getProjectionMatrix());
    m_mainShader->setUniform("view", mat4::identity());
    m_mainShader->setUniform("model", model);

        texture->bind();
            m_inventory->render();
        texture->unbind();

    m_mainShader->unbind();

    glEnable(GL_DEPTH_TEST);

    m_window->update();
}
