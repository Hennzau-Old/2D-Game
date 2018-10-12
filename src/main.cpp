#include "game.h"

using namespace maths;
using namespace std;

const int       FRAME_CAP = 6666;

int main(void)
{
    /*
    const char* FILENAME = "res/a.txt";

    int toRestore[4];
    ifstream i(FILENAME, ios::binary);

    i.read((char* ) &toRestore, sizeof(toRestore));

    for(int i = 0; i < sizeof(toRestore); i++)
    {
        printf("%d\n", toRestore[i]);
    }

    int toStore[4] = {13, 6, 15, 1};
    ofstream o(FILENAME, ios::binary);

    o.write((char*) &toStore, sizeof(toStore));
    o.close();
    */

    Game    *game = new Game();

    double  tickTime = 1.0 / 60.0;
    double  renderTime = 1.0 / FRAME_CAP;

    double  lastTickTime = glfwGetTime(), timer = lastTickTime;
    double  lastRenderTime = glfwGetTime();
    double  deltaTime = 0,
            nowTime = 0;

    int     frames = 0,
            ticks = 0;

    while(!game->getWindow()->isClosed())
    {
        nowTime = glfwGetTime();
        deltaTime += (nowTime - lastTickTime) / tickTime;
        lastTickTime = nowTime;

        while(deltaTime >= 1.0)
        {
            ticks++;
            game->update();
            deltaTime--;
        }

        if(nowTime - lastRenderTime >= renderTime)
        {
            lastRenderTime = nowTime;
            game->render();
            frames++;
        }

        if(glfwGetTime() - timer > 1.0)
        {
            timer++;
            printf("FPS : %d | TPS : %d \n", frames, ticks);
            frames = 0;
            ticks = 0;
        }
    }

    delete game;

    return 0;
}
