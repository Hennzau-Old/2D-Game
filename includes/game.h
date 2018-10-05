#ifndef GAME
#define GAME

#include "window.h"
#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "world.h"

class Game
{
    public:
        Game();
        ~Game();
        void      update();
        void      render();

        Window    *getWindow() { return m_window; }
        Shader    *getMainShader() { return m_mainShader; }
        Input     *getInput() { return m_input; }
        Camera    *getCamera() { return m_camera; }
        Player    *getPlayer() { return m_player; }

    private:
        Window        *m_window;
        Shader        *m_mainShader;
        Input         *m_input;
        Camera        *m_camera;
        Player        *m_player;
        World         *m_world;

        std::vector<float>    m_vertices;

        GLuint                m_vao,
                              m_vbo;
};

#endif
