#ifndef GAME_H
#define GAME_H

#include "Gladiator.h"
#include "Gladiator_Listener.h"
#include "GxSingleton.h"
#include "Weapon.h"
#include <vector>
#include <map>

class Game : public Gladiator_Listener, public GX::Singleton<Game>
{
    public:
        Game();
        virtual ~Game();

        void run();

        //initialisieren: Waffen laden
        bool init();

        void message(const std::string& msg);

        std::map<std::string, Weapon*> getWeapons() {return mWeapons;}

        virtual void died(const Gladiator* gladiator);
        virtual void inflictedDamage(const Gladiator* gladiator, const Gladiator* victim, int amount);
    protected:
        bool mRun;

        std::map<std::string, Weapon*> mWeapons;

        std::vector<Gladiator> mGladiators;
    private:
};

#endif // GAME_H
