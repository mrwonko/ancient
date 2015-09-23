#include "Game.h"
#include "CLArguments.h"
#include "csvparser.h"
#include <iostream>

int main(int argc, char** argv)
{
    //die CLArguments initialisieren
    cppag::CLArguments::CLArguments(argc, argv);

    Game myGame = Game();

    //initialisieren
    if(myGame.init())
        myGame.run();
    else
        std::cout<<"Initialisierung fehlgeschlagen!";

    return (0);
}
