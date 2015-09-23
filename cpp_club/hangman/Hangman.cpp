#include "Hangman.h"
#include <algorithm>
#include <time.h>

Hangman::Hangman(std::string word)
{
    mWord=word;
    mTries = 0;
}

Hangman::~Hangman()
{
    //dtor
}

bool Hangman::run()
{
    while (mWord != getUserWord() && mTries < mMaxTries)
    {
        round();
        std::cout << getUserWord();
    }
    std::cout<<std::endl;

    return true;
}

void Hangman::round()
{
    char selection;
    do
    {
        std::cout << "Gib mir einen Buchstaben";
        if(mUsed.size() > 0)
        {
            std::cout << "(schon versucht: ";
            for(unsigned int i = 0; i < mUsed.size(); ++i)
            {
                std::cout<<mUsed.at(i);
            }
            std::cout << ")";
        }
        std::cout << ": ";
        std::cin >> selection;
    }
    while(alreadyTried(selection));

    mUsed.push_back(selection);

    if(isInWord(selection)) ++mTries;

    std::cout << "Noch "<<mMaxTries-mTries<<" von "<<mMaxTries<<" Versuchen."<<std::endl;
}

bool Hangman::alreadyTried(char c)
{
    std::vector<char>::iterator result = std::find(mUsed.begin(), mUsed.end(), c);
    char notC;
    if(c >='A' && c <='Z')
    {
        notC = c - ('A'-'a');
    }
    else
    {
    	notC = c + ('A'-'a');
    }
    std::vector<char>::iterator notResult = std::find(mUsed.begin(), mUsed.end(), notC);
    return(result != mUsed.end() || notResult!=mUsed.end());
}

//If a given char is in the desired word
bool Hangman::isInWord(char selection)
{
    if(selection >= 'A' && selection <= 'Z') selection -= 'A'-'a';
    std::string::size_type correct = mWord.find(selection);
    return(correct == std::string::npos);
}

std::string Hangman::getUserWord()
{
    std::string copy = mWord;
    for(unsigned int i=0; i<mWord.size(); ++i)
    {
        if(!alreadyTried(copy[i])) copy[i] = '_';
        /*
        std::vector<char>::iterator result;
        //Erst wird nach dem Buchstaben gesucht, wird er nicht gefunden, so sucht man auch nach dem Buchstaben in gross/kleinschreibung anders.
        result = std::find(mUsed.begin(),mUsed.end(),copy[i])!=mUsed.end() ? std::find(mUsed.begin(),mUsed.end(),copy[i]) : std::find(mUsed.begin(),mUsed.end(), ( (copy[i]>='A'&&copy[i]<='Z') ? copy[i] - ('A'-'a') : copy[i] + ('A'-'a')));
        if(result==mUsed.end())
        {
            //nicht gefunden
            copy[i] = '_';
        }
        else
        {
            //gefunden
        }
        */
    }

    return copy;
}
