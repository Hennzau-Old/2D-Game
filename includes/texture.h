#ifndef TEXTURE
#define TEXTURE

#include <GL/glew.h>

#include "maths.h"

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <cstring>
#include <vector>

#include <iostream>
#include <fstream>

class Texture
{
    public:
        Texture(const char* path, int v);
        ~Texture();

        void          bind();
        void          unbind();

        GLuint        getID() { return m_id; }

    private:
        GLuint        m_id;

        int           m_width,
                      m_height;

};

#endif
