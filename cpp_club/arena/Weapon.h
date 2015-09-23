#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "csvline.h"

class Weapon
{
    public:
        Weapon();
        Weapon(const std::string& name, int basedamage, int numdice, int dicesides);
        //give a line of a csvfile, parse it.
        Weapon(const cppag::CSVLine &csvline);
        virtual ~Weapon();

        // Schaden ausrechnen
        const int& calculateDamage () const;

        std::string toString();

    protected:
        int mBaseDamage;
        int mNumDice;
        int mDiceSides;
        std::string mName;
};

#endif // WEAPON_H
