#ifndef CHUNK
#define CHUNK

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "tile.h"
#include "world.h"

const int                     CHUNK_SIZE = 16;

class World;

class Chunk
{
    public:
        Chunk(int x, int y, World *world);
        ~Chunk();


        void                  update();
        void                  render();

        void                  createChunk();
        void                  generateChunk();
        void                  generateBuffers();
        void                  updateBuffers();

        int                   getTile(int x, int y);
        int                   setTile(int x, int y, int tile);

        int                   getX() { return m_x; }
        int                   getY() { return m_y; }

    private:
        int                   m_verticescount = 0;
        int                   m_x,
                              m_y;

        GLuint                m_vao,
                              m_vbo,
                              m_cbo;

        int**                 m_tiles;

        World*                m_world;

        std::vector<float>    m_vertices;

};

#endif
