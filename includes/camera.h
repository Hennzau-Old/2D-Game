#ifndef CAMERA
#define CAMERA

#include "window.h"
#include "player.h"
#include "input.h"
#include "transform.h"

class Player;

class Camera
{
    public:
        Camera(Input *input, Window *window);
        ~Camera();

        void          update(Player *player);
        void          setOrthographic(float znear, float zfar);

        void          setX(float x) { m_pos.x = x; }
        void          setY(float y) { m_pos.y = y; }

        void          setRX(float rx) { m_rot.x = rx; }
        void          setRY(float ry) { m_rot.y = ry; }

        float         getX() { return m_pos.x; }
        float         getY() { return m_pos.y; }

        float         getRX() { return m_rot.x; }
        float         getRY() { return m_rot.y; }

        float         getNear() { return m_znear; }
        float         getFar() { return m_zfar; }
        float         getAspect() { return m_aspect; }

        Transform     getTransform() { return m_transform; }

        maths::mat4   getProjectionMatrix() { return m_projection; }
        maths::mat4   getViewMatrix() { return m_view; }

        maths::vec2   getPos() { return m_pos; }
        maths::vec2   getRot() { return m_rot; }

        Input           *getInput() { return m_input; }

    private:
        maths::vec2   m_pos,
                      m_rot;

        maths::mat4   m_projection,
                      m_view,
                      m_oview;

        float         m_znear,
                      m_zfar,
                      m_aspect;

        Transform     m_transform;

        Input         *m_input;
        Window        *m_window;

        void          move(float xa, float ya);
};

#endif
