#include "tile.h"

using namespace maths;

void Tile::addTile(std::vector<float> *v, int x, int y, float width, float height, maths::vec3 tile, int imgWidth, int imgHeight)
{
  //  printf("%f - %f \n", tile.x, tile.y);

    putVertices(v, x + width * TILE_SIZE, y,                          (1 + tile.x) / imgWidth, (0 + tile.y) / imgHeight);
    putVertices(v, x + width * TILE_SIZE, y + height * TILE_SIZE,     (1 + tile.x) / imgWidth, (1 + tile.y) / imgHeight);
    putVertices(v, x, y + height * TILE_SIZE,                         (0 + tile.x) / imgWidth, (1 + tile.y) / imgHeight);

    putVertices(v, x, y,                                              (0 + tile.x) / imgWidth, (0 + tile.y) / imgHeight);
    putVertices(v, x + width * TILE_SIZE, y,                          (1 + tile.x) / imgWidth, (0 + tile.y) / imgHeight);
    putVertices(v, x, y + height * TILE_SIZE,                         (0 + tile.x) / imgWidth, (1 + tile.y) / imgHeight);
}

void Tile::putVertices(std::vector<float> *v, int x, int y, float xl, float yl)
{
    v->push_back(x);
    v->push_back(y);

    v->push_back(xl);
    v->push_back(yl);
}
