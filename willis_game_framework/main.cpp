#include "WGF/gameFramework.h"
#include "PongGame.h"

//TODO StringSystem

int main()
{
    WGF::GameFramework gameFramework = WGF::GameFramework();
    if(!gameFramework.Init())
    {
        return 0;
    }
    //TestGame - Pong
    PongGame pong = PongGame();
    gameFramework.AddGame(&pong);
    gameFramework.StartGame(&pong);
    gameFramework.Start();
    return 0;
}
