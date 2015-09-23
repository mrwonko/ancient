#include "Game.h"
#include "GameFramework.h"
#include "InputActionButton.h"

#include <SFML/Window/Event.hpp>

namespace WGF
{

    Game::Game(const std::string& name) :
        mName(name),
        mRenderWindow(GameFramework::GetSingleton().GetRenderWindow())
    {
        //ctor
    }

    Game::~Game()
    {
        //dtor
    }

    void Game::Stop()
    {
        mRenderWindow.Clear();
        mRenderWindow.Display();
        GameFramework::GetSingleton().StopGame(this);
    }

    bool Game::Init(bool init)
    {
        if(init)
        {
            return Init();
        }
        for(std::vector<InputAction*>::iterator it = mInputActions.begin(); it != mInputActions.end(); ++it)
        {
            delete (*it);
        }
        return Deinit();
    }

    bool Game::IsPressed(unsigned long act_ID)
    {
        //search for key in common actions
        for(std::vector<InputActionButton*>::iterator it = mCommonButtonActions.begin(); it != mCommonButtonActions.end(); ++it)
        {
            if((*it)->GetID() == act_ID)
            {
                return (*it)->IsPressed();
            }
        }
        //search for key in game actions
        for(std::vector<InputAction*>::iterator it = mInputActions.begin(); it != mInputActions.end(); ++it)
        {
            if((*it)->GetID() == act_ID)
            {
                if((*it)->GetType() == InputAction::INPUT_ACTION_BUTTON)
                {
                    return ((InputActionButton*) (*it))->IsPressed();
                }
                break;
            }
        }
        return false;
    }

    std::vector<InputActionButton*> Game::mCommonButtonActions;
} // namespace WGF
