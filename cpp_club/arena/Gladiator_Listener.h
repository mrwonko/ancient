#ifndef GLADIATOR_LISTENER_H
#define GLADIATOR_LISTENER_H

#include <string>
class Gladiator;

class Gladiator_Listener
{
    public:
        Gladiator_Listener();
        virtual ~Gladiator_Listener();

        virtual void died(const Gladiator* gladiator) = 0;
        virtual void inflictedDamage(const Gladiator* gladiator, const Gladiator* victim, int amount) = 0;

    protected:
    private:
};

#endif // GLADIATOR_LISTENER_H
