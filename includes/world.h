#ifndef WORLD
#define WORLD

#include "chunk.h"
#include <vector>
#include <iostream>

const int               WORLD_SIZE = 5;

class Chunk;


class World
{
    public:
        World();
        ~World();

        void            update();
        void            render();

        void            updateChunk(int x, int y);
        void            updateChunks(int x, int y);
        void            updateChunkAtBlock(int x, int y);
        void            updateChunksAtBlock(int x, int y);

        int             setTile(int x, int y, int tile);
        int             getTile(int x, int y);
        int             getTypeTile(std::string name);

        Chunk           *getChunkFromTile(int x, int y);

        std::vector<int> tilestype;

    private:
        Chunk           *m_chunks[WORLD_SIZE * WORLD_SIZE];
        std::vector<std::string> tilestype_name;
};

#endif
