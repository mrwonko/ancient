#ifndef HANGMAN_H
#define HANGMAN_H

#include <string>
#include <vector>
#include <iostream>

class Hangman
{
    public:
        Hangman(std::string word);
        virtual ~Hangman();

        // Startet die Hangman Partie
        bool run();
    protected:
        // Einzelne Benutzereingabe
        void round();
    private:
        // Ob ein Buchstabe im zu erratenden Wort ist - ignoriert gross-/kleinschreibung
        bool isInWord(char);
        // Ob ein Buchstabe schon mal geraten wurde - ignoriert gross-/kleinschreibung
        bool alreadyTried(char);
        // Das zu erratenden Wort
        std::string mWord;

        // Vom Benutzer schon "probierte" Zeichen
        std::vector<char> mUsed;

        // Anzahl der Versuche
        static const unsigned int mMaxTries=6;
        unsigned int mTries;

        // Gibt das vom Benutzer bisher erratene Wort zurueck
        std::string getUserWord();
};

#endif // HANGMAN_H
