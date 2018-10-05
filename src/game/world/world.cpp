#include "world.h"
#include "loader.h"

World::World()
{
    std::string s = Loader::loadFile("res/tiles.txt");

    std::vector<std::string> v = Loader::split(s, "\n");

    for(int i = 0; i < v.size() - 1; i++)
    {
        std::vector<std::string> vs = Loader::split(v[i], ";");

        tilestype_name.push_back(vs[0]);

        int x = std::stoi(vs[1].c_str());
        int y = std::stoi(vs[2].c_str());
        int z = std::stoi(vs[3].c_str());

        tilestype.push_back(maths::vec3((float) x, (float) y, (float) z).pack());
    }

    for(int x = 0; x < WORLD_SIZE; x++)
    {
        for(int y = 0; y < WORLD_SIZE; y++)
        {
            m_chunks[x + y * WORLD_SIZE] = new Chunk(x, y, this);
        }
    }

    for(int i = 0; i < WORLD_SIZE * WORLD_SIZE; i++)
    {
        m_chunks[i]->generateChunk();
    }

    for(int i = 0; i < WORLD_SIZE * WORLD_SIZE; i++)
    {
        m_chunks[i]->generateBuffers();
    }
}

World::~World()
{
    for(int i = 0; i < WORLD_SIZE * WORLD_SIZE; i++)
    {
        delete m_chunks[i];
    }
}

void World::update()
{
    for(int i = 0; i < WORLD_SIZE * WORLD_SIZE; i++)
    {
        m_chunks[i]->update();
    }
}

void World::render()
{
    for(int i = 0; i < WORLD_SIZE * WORLD_SIZE; i++)
    {
        m_chunks[i]->render();
    }
}

void World::updateChunk(int x, int y)
{

}

void World::updateChunks(int x, int y)
{

}

void World::updateChunkAtBlock(int x, int y)
{

}

void World::updateChunksAtBlock(int x, int y)
{

}

int World::setTile(int x, int y, int tile)
{
    Chunk *chunk = getChunkFromTile(x, y);

    if(chunk == NULL)
        return 0;

    int xb = x % CHUNK_SIZE;
    int yb = y % CHUNK_SIZE;

    return chunk->setTile(xb, yb, tile);
}

int World::getTile(int x, int y)
{
    Chunk *chunk = getChunkFromTile(x, y);

    if(chunk == NULL)
        return 0;

    int xb = x % CHUNK_SIZE;
    int yb = y % CHUNK_SIZE;

    return chunk->getTile(xb, yb);
}

Chunk* World::getChunkFromTile(int x, int y)
{
    int xc = x / CHUNK_SIZE;
    int yc = y / CHUNK_SIZE;

    if(xc < 0 || yc < 0 || xc >= CHUNK_SIZE || yc >= CHUNK_SIZE)
        return NULL;

    return m_chunks[xc + yc * WORLD_SIZE];
}

int World::getTypeTile(std::string name)
{
    for(int i = 0; i < tilestype_name.size(); i++)
    {
        if(!tilestype_name[i].compare(name))
        {
            return tilestype[i];
        }
    }
    return 0;
}
