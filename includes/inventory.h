#ifndef INVENTORY
#define INVENTORY

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "world.h"
#include "game.h"

class Inventory
{
    public:
        Inventory(World *world);
        ~Inventory();

        void                  update();
        void                  render();

        int                   getItem(int x, int y);
        int                   setTime(int x, int y, int item);

        void                  setVisible(bool v);
        bool                  isVisible() { return m_visible; }

    private:
        int                   m_verticescount = 0;
        int**                 m_items;

        bool                  m_visible = true;

        GLuint                m_vao,
                              m_vbo;

        World*                m_world;

        std::vector<float>    m_vertices;

};

#endif
