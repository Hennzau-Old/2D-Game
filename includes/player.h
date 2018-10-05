#ifndef PLAYER
#define PLAYER

#include "input.h"
#include "maths.h"
#include "shader.h"
#include "camera.h"
#include "texture.h"

class Camera;
class World;

class Player
{
    public:
        Player(Input *input, World *world);
        ~Player();

        void          update();
        void          render(Shader *shader, Camera *camera);

        void          updateSprite();

        maths::vec2   getPos() { return m_pos; }
        maths::vec2   getRot() { return m_rot; }

        void          setX(float x) { m_pos.x = x; }
        void          setY(float y) { m_pos.y = y; }

        float         getX() { return m_pos.x; }
        float         getY() { return m_pos.y; }


        maths::vec2   m_pos,
                      m_rot;

        bool          debug_mode = false;

    private:
        Input         *m_input;
        World         *m_world;

        Texture       *m_texture;

        GLuint        m_vao,
                      m_vbo;

        std::vector<float> m_vertices;

        void          move(float xa, float ya);
        bool          isColliding(float xa, float ya);
};

#endif
