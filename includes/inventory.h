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

        void                  update(Input *input);
        void                  render();

        int                   getItem(int x, int y);
        int                   setTime(int x, int y, int item);
        int                   getSelectedItem() { return item_selected; }

        void                  setVisible(bool v);
        void                  setItem(int item);
        
        bool                  isVisible() { return m_visible; }

    private:
        int                   m_verticescount = 0;
        int                   item_selected = 0;
        int**                 m_items;

        bool                  m_visible = true;

        GLuint                m_vao,
                              m_vbo;

        World*                m_world;

        std::vector<float>    m_vertices;

};

#endif
