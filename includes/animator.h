#ifndef ANIMATOR
#define ANIMATOR

class Animator
{
    public:
        Animator(int length, int speed, bool loop);
        ~Animator();

        void          update();
        void          play();
        void          stop();
        void          pause();

        int           getCurrentFrame();

        bool          isPlaying();

    private:
        int           m_length,
                      m_speed,
                      m_frame,
                      m_time;

        bool          m_loop,
                      m_playing;

};

#endif
