#include "animator.h"

Animator::Animator(int length, int speed, bool loop)
{
    m_length = length;
    m_speed = speed;
    m_loop = loop;
    m_frame = 0;
}

Animator::~Animator()
{

}

void Animator::update()
{
    if(m_playing)
    {
        m_time++;
        if(m_time > m_speed)
        {
            m_frame++;
            if(m_frame >= m_length)
            {
                if(m_loop) m_frame = 0;
                else m_frame = m_length - 1;
            }
            m_time = 0;
        }
    }
}

void Animator::play()
{
    m_playing = true;
}

void Animator::stop()
{
    m_playing = false;
    m_frame = 0;
}

void Animator::pause()
{
    m_playing = false;
}

bool Animator::isPlaying()
{
    return m_playing;
}

int Animator::getCurrentFrame()
{
    return m_frame;
}
