#ifndef LOADER
#define LOADER

#include "maths.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Loader
{
    public:
        static std::string loadFile(const char* path);
        static std::vector<std::string> split(std::string str, std::string del);
};

#endif
