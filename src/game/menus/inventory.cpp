#include "inventory.h"

using namespace maths;

int wm = 4;
int hm = 6;

int w = WIDTH / TILE_SIZE - wm;
int h = HEIGHT / TILE_SIZE - hm;

Inventory::Inventory(World *world)
{
    m_world = world;

    m_items = new int*[w];

    for(int i = 0; i < w; i++)
    {
        m_items[i] = new int[h];
    }

    int i = 0;

    for(int x = 0; x < w; x++)
    {
        for(int y = 0; y < h; y++)
        {
            if(m_world->getTile(i) != 0) m_items[x][y] = m_world->getTile(i);

            else m_items[x][y] = 0;

            i++;
        }
    }

    for(int x = 0; x < w; x++)
    {
        for(int y = 0; y < h; y++)
        {
            if(m_items[x][y] == 0)
                continue;

            Tile::addTile(&m_vertices, y * TILE_SIZE * 2 + (wm / 2 * TILE_SIZE * 2), x * TILE_SIZE * 2 + (hm / 2 * TILE_SIZE * 2), 2, 2, vec3::unpack(m_items[x][y]), 16, 16);
            m_verticescount += 6;
        }
    }

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

Inventory::~Inventory()
{

}

void Inventory::update()
{

}

void Inventory::render()
{
    if(!m_visible)
        return;

    glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, m_verticescount);
    glBindVertexArray(0);
}

void Inventory::setVisible(bool v)
{
    m_visible = v;
}