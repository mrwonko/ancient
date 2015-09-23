#include "Game.h"
#include "Gladiator.h"
#include "Gladiator_Listener.h"
#include <iostream>
#include "csvparser.h"

Game::Game()
{
    mRun = true;
}

Game::~Game()
{
    //dtor
}

void Game::message(const std::string& message)
{
        std::cout << message << std::endl;
}

void Game::run()
{
    Weapon Axt = Weapon("Axt", 6, 1, 6);

    mGladiators.push_back(Gladiator());
    mGladiators.push_back(Gladiator("Willi", Axt, 25));

    for (unsigned int i=0; i<mGladiators.size(); i++)
    {
        mGladiators[i].registerListener(this);
    }

    // Spielschleife
    for (int runde = 1; mRun; ++runde)
    {
        std::cout << "Das ist die " << runde << ". Runde!" << std::endl;

        // Spieler greifen sich an
        mGladiators[0].attack(mGladiators[1]);
        mGladiators[1].attack(mGladiators[0]);

        // Lebt noch jemand?
        for (unsigned int i=0; i<mGladiators.size(); i++)
        {
            if (!mGladiators[i].isAlive())
                mGladiators[i].reportDeath();
        }
    }
}

bool Game::init()
{
    cppag::CSVParser weaponparser("data/weapons.csv", ",");
    weaponparser.parse();

    //Für jede Zeile = Waffe tue:
    for(unsigned int i = 0; i < weaponparser.size(); ++i)
    {
        //weaponparser[i] is the current line
        //weaponparser[i][0] is the Name
        //weaponparser[i] is the CSVLine containing the info for the constructor - why am I mixing german and english comments?
        mWeapons[weaponparser[i][0]] = new Weapon(weaponparser[i]);
    }
    return (true);
}

void Game::died(const Gladiator* gladiator)
{
    std::cout << "\"" << gladiator->getName() << "\" ist gestorben!" << std::endl;
    mRun = false;
}

void Game::inflictedDamage(const Gladiator* gladiator, const Gladiator* victim, int amount)
{
    std::cout << "\"" << gladiator->getName() << "\" macht " << amount << " Schaden an \"" << victim->getName() << "\"" << std::endl;
}

// Singleton Implementierung
template<> Game* GX::Singleton<Game>::ms_Singleton = 0;
