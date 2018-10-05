#include "chunk.h"

const int vegetation_part = 6;

Chunk::Chunk(int x, int y, World *world)
{
    m_world = world;

    m_x = x;
    m_y = y;

    createChunk();
}

Chunk::~Chunk()
{
    for(int i = 0; i < CHUNK_SIZE; i++)
    {
        delete [] m_tiles[i];
    }

    delete [] m_tiles;
}

void Chunk::update()
{

}

void Chunk::render()
{
    glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, m_verticescount);
    glBindVertexArray(0);
}

void Chunk::createChunk()
{
    m_tiles = new int*[CHUNK_SIZE];

    for(int i = 0; i < CHUNK_SIZE; i++)
    {
        m_tiles[i] = new int[CHUNK_SIZE];
    }
    for(int x = 0; x < CHUNK_SIZE; x++)
    {
        for(int y = 0; y < CHUNK_SIZE; y++)
        {
  //          int random = rand() % ((m_typetiles.size() - vegetation_part - 1 - 0) + 1) + 0;

            m_tiles[x][y] = m_world->tilestype[0];
        }
    }

}

void Chunk::generateChunk()
{
    for(int x = 0; x < CHUNK_SIZE; x++)
    {
        for(int y = 0; y < CHUNK_SIZE; y++)
        {
            int tile = m_tiles[x][y];

            int xx = (m_x * CHUNK_SIZE + x) * TILE_SIZE;
            int yy = (m_y * CHUNK_SIZE + y) * TILE_SIZE;

            Tile::addTile(&m_vertices, xx, yy, 1, 1, maths::vec3::unpack(tile), 16, 16);

            m_verticescount += 6;
        }
    }
}

void Chunk::generateBuffers()
{
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

int Chunk::getTile(int x, int y)
{
    if(x < 0 || y < 0 || x >= CHUNK_SIZE || y >= CHUNK_SIZE)
        return 0;

    return m_tiles[x][y];
}

int Chunk::setTile(int x, int y, int tile)
{
    if(x < 0 || y < 0 || x >= CHUNK_SIZE || y >= CHUNK_SIZE)
        return 1;

    if(m_tiles[x][y] == tile) return 1;

    m_tiles[x][y] = tile;

    return 0;
}
