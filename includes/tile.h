#ifndef TILE
#define TILE

#include "maths.h"
#include <vector>
#include <iostream>

const int                     TILE_SIZE = 32;

class Tile
{
    public:
      static void             addTile(std::vector<float> *v, int x, int y, float width, float height, maths::vec3 tile, int imgWidth, int imgHeight);

    private:
      static void             putVertices(std::vector<float> *v, int x, int y, float xl, float yl);
};

#endif
