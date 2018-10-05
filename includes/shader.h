#ifndef SHADER
#define SHADER

#include <GL/glew.h>

#include "maths.h"
#include "loader.h"

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <cstring>
#include <vector>

#include <iostream>
#include <fstream>

class Shader
{
    public:
        Shader(const char* vPath, const char* fPath);
        ~Shader();

        void          bind();
        void          unbind();
        void          setUniform(const char* name, maths::mat4 matrix);
        void          setUniform(const char* name, float a);
        void          setUniform(const char* name, int a);
        void          setUniform(const char* name, maths::vec3 a);

        GLuint        getID() { return id; }

    private:
        GLuint        id;

};

#endif
