#include "Gladiator.h"
#include <iostream>
#include <vector>
#include "game.h"
//TODO: c++ version von fflush()?
#include <cstdio>

Gladiator::Gladiator(const std::string& name, Weapon& weapon, int hitpoints)
: mWeapon(weapon), mName(name)
{
    mHitPoints = hitpoints;
    mListener = NULL;
}

Gladiator::Gladiator()
{
    std::cout << "Wie soll der Gladiator heissen? ";
    std::cin >> mName;
    std::cout << std::endl<<std::endl;

    mWeapon = chooseWeapon();
    mHitPoints = 30;

    std::cout << "Lebenspunkte: " << mHitPoints << std::endl;

    mListener = NULL;
}

Gladiator::Gladiator (std::string directory)
{
    cppag::CSVParser myParser (directory, ",");
    myParser.parse ();
}

Gladiator::~Gladiator()
{
    //dtor
}

int Gladiator::attack(Gladiator& victim)
{
    // Opfer schaden zufügen, aber mit unserer Waffe
    int damage = victim.inflictDamage(mWeapon);

    // Listener aufrufen
    mListener->inflictedDamage(this, &victim, damage);

    return (0);
}

int Gladiator::inflictDamage(Weapon& weapon)
{
    int damage = weapon.calculateDamage();
    mHitPoints -= damage;

    return (damage);
}

bool Gladiator::isAlive()
{
    return (mHitPoints > 0);
}

void Gladiator::reportDeath()
{
    if (mListener != NULL)
        mListener->died(this);
}

void Gladiator::registerListener(Gladiator_Listener* listener)
{
    mListener = listener;
}

Weapon Gladiator::chooseWeapon()
{
    // Waffenkammer auffüllen
    std::map<std::string, Weapon*> weapons;
    weapons = Game::getSingleton().getWeapons();

    fflush(stdin);

    // Eingabe verlangen
    while (true)
    {
        std::string choice = "";
        std::cout<<"Welche Waffe möchtest du haben?"<<std::endl;

        // Waffen ausgeben
        for (std::map<std::string, Weapon*>::iterator it = weapons.begin(); it != weapons.end(); ++it)
        {
            std::cout <<  (*(it->second)).toString();
        }

        // Benutzereingabe
        std::getline(std::cin, choice);

        // Eingabe validieren
        if (weapons.count(choice) > 0)
            //TODO: auch hier weapon* statt weapon benutzen?
            return (*weapons[choice]);
    }
}
