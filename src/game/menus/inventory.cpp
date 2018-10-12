#include "inventory.h"

using namespace maths;

int w = 9;
int h = 5;

Inventory::Inventory(World *world)
{
    m_world = world;

    m_items = new int*[w];

    item_selected = world->getTypeTile("GRASS");

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

            Tile::addTile(&m_vertices, x * TILE_SIZE * 2 + WIDTH / 4, y * TILE_SIZE * 2 + HEIGHT / 4, 2, 2, vec3::unpack(m_items[x][y]), 16, 16);
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

void Inventory::update(Input *input)
{
    if(!m_visible)
        return;

    int x = (input->getX() - (WIDTH / 4)) / (TILE_SIZE * 2);
    int y = (input->getY() - (HEIGHT / 4)) / (TILE_SIZE * 2);

    if(input->getButtonDown(0))
    {
        printf("%d / %d\n", x, y);
        if(x > 0 && y > 0 && x <= w && y <= h)
        {
            if(m_items[x][y] != 0)
            {
                item_selected = m_items[x][y];
            }
        }
    }
}

void Inventory::setItem(int item)
{
    item_selected = item;
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
