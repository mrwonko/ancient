#ifndef GLADIATOR_H
#define GLADIATOR_H

#include <string>
#include "Gladiator_Listener.h"
#include "Weapon.h"
#include "csvparser.h"

class Gladiator
{
    public:
        Gladiator(const std::string& name, Weapon& weapon, int hitpoints);
        Gladiator();
        Gladiator (std::string directory);
        virtual ~Gladiator();

        int attack(Gladiator& victim);
        int inflictDamage(Weapon& weapon);

        bool isAlive();
        const std::string& getName() const  {return (mName);}

        void reportDeath();

        void registerListener(Gladiator_Listener* listener);

    protected:
        Weapon chooseWeapon();

    protected:
        int         mHitPoints;
        Weapon      mWeapon; //TODO: lieber weapon* benutzen?
        std::string mName;

        Gladiator_Listener* mListener;
};

#endif // GLADIATOR_H
