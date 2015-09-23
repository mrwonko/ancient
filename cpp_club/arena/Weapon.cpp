#include "Weapon.h"
#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>

Weapon::Weapon()
: mName()
{
    mBaseDamage = 0;
    mNumDice = 0;
    mDiceSides = 0;
}

Weapon::Weapon(const std::string& name, int basedamage, int numdice, int dicesides)
 : mName(name)
{
    mBaseDamage = basedamage;
    mNumDice = numdice;
    mDiceSides = dicesides;
}

Weapon::Weapon(const cppag::CSVLine &csvline) : mName("fehlerhafter Eintrag!")
{
    if(csvline.size()<4) //too few info in line?
    {
        mBaseDamage = 0;
        mNumDice = 0;
        mDiceSides = 0;
        return;
    }
    //laden
    mName = csvline[0];
    //extra scope für stringstream da schwer zu leeren
    {
        std::stringstream ss; //Konvertierung string -> int;
        ss<<csvline[1];
        ss>>mBaseDamage;
    }
    {
        std::stringstream ss; //Konvertierung string -> int;
        ss<<csvline[2];
        ss>>mNumDice;
    }
    {
        std::stringstream ss; //Konvertierung string -> int;
        ss<<csvline[3];
        ss>>mDiceSides;
    }
}

Weapon::~Weapon()
{
    //dtor
}

const int& Weapon::calculateDamage() const
{
    int damage = 0;

    damage += mBaseDamage;

    for (int i = 0; i < mNumDice; ++i)
    {
        // Zufallszahlengenerator initialisieren
        srand(time(NULL));

        damage += rand() % mDiceSides;
        damage += 1;

        sleep(1);
    }

    return (damage);
}

std::string Weapon::toString()
{
    // #include <sstream>
    std::stringstream stream;
    stream << mName << ", " << mBaseDamage << " + " << mNumDice << "W" << mDiceSides << std::endl;

    // Sonst hätten wir das hier
    std::string string;
    string += mName;
    string += ", ";
    string += mBaseDamage;
    // ...
    return (stream.str());
}
