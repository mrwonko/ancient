#include "InputManager.h"
#include "InputActionButton.h"
#include "Game.h"
#include "GameFramework.h"
#include "Logfile.h"

namespace WGF
{

    InputManager::InputManager()
    {
        //ctor
        GameFramework::GetSingleton().GetLogfile().Log("The InputManager greets the World: \"Hello World!\"");
    }

    void InputManager::Init()
    {
        GameFramework::GetSingleton().GetLogfile().Log("InputManager initializing...");
        //create the common actions if necessary
        //needs to access the InputManager via the Framework so it has to be available there and I think it's not until it's finished construction
        if(Game::mCommonButtonActions.size() == 0)
        {
            GameFramework::GetSingleton().GetLogfile().Log("- creating common actions");
            InputListener* framework = GameFramework::GetSingletonPtr();
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_UP, "@MOVE_UP_FORWARD", "@MOVE_UP_FORWARD_DESC", framework, sf::Key::Up));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_DOWN, "@MOVE_DOWN_BACKWARD", "@MOVE_DOWN_BACKWARD_DESC", framework, sf::Key::Down));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_LEFT, "@MOVE_TURN_LEFT", "@MOVE_TURN_LEFT_DESC", framework, sf::Key::Left));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_RIGHT, "@MOVE_TURN_RIGHT", "@MOVE_TURN_RIGHT_DESC", framework, sf::Key::Right));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_ATTACK, "@ATTACK", "@ATTACK_DESC", framework, sf::Key::LShift));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_ATTACK2, "@ATTACK2", "@ATTACK2_DESC", framework, sf::Key::LControl));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_USE, "@USE", "@USE_DESC", framework, sf::Key::E));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_JUMP, "@JUMP", "@JUMP_DESC", framework, sf::Key::Space));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_ITEM1, "@ITEM1", "@ITEM1_DESC", framework, sf::Key::Num1));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_ITEM2, "@ITEM2", "@ITEM2_DESC", framework, sf::Key::Num2));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_ITEM3, "@ITEM3", "@ITEM3_DESC", framework, sf::Key::Num3));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_ITEM4, "@ITEM4", "@ITEM4_DESC", framework, sf::Key::Num4));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_ITEM5, "@ITEM5", "@ITEM5_DESC", framework, sf::Key::Num5));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_ITEM6, "@ITEM6", "@ITEM6_DESC", framework, sf::Key::Num6));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_ITEM7, "@ITEM7", "@ITEM7_DESC", framework, sf::Key::Num7));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_ITEM8, "@ITEM8", "@ITEM8_DESC", framework, sf::Key::Num8));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_ITEM9, "@ITEM9", "@ITEM9_DESC", framework, sf::Key::Num9));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_ITEM10, "@ITEM10", "@ITEM10_DESC", framework, sf::Key::Num0));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_PAUSE, "@PAUSE", "@PAUSE_DESC", framework, sf::Key::P));
            Game::mCommonButtonActions.push_back(new InputActionButton(Game::ACT_STOP, "@STOP", "@STOP_DESC", framework, sf::Key::Escape));
        }
        GameFramework::GetSingleton().GetLogfile().Log("InputManager initialized!");
    }

    InputManager::~InputManager()
    {
        //dtor
        for(std::vector<InputActionButton*>::iterator it = Game::mCommonButtonActions.begin(); it != Game::mCommonButtonActions.end(); ++it)
        {
            delete (*it);
        }
        Game::mCommonButtonActions.clear();
        for(std::map<InputListener*, GameInputMapping*>::iterator it = mInputMappings.begin(); it != mInputMappings.end(); ++it)
        {
            delete it->second;
        }
    }

    void InputManager::KeyPressed (const sf::Event::KeyEvent& keyEvent)
    {
        TellAboutKeyEvent(GameFramework::GetSingletonPtr(), keyEvent, true);
        if(GameFramework::GetSingleton().GetCurrentGame())
        {
            TellAboutKeyEvent(GameFramework::GetSingleton().GetCurrentGame(), keyEvent, true);
        }
    }

    void InputManager::KeyReleased (const sf::Event::KeyEvent& keyEvent)
    {
        TellAboutKeyEvent(GameFramework::GetSingletonPtr(), keyEvent, false);
        if(GameFramework::GetSingleton().GetCurrentGame())
        {
            TellAboutKeyEvent(GameFramework::GetSingleton().GetCurrentGame(), keyEvent, false);
        }
    }

    void InputManager::TellAboutKeyEvent(InputListener* who, const sf::Event::KeyEvent& keyEvent, const bool pressed)
    {
        //are there any key-action-mappings for this listener?
        std::map<InputListener*, GameInputMapping*>::iterator inputMapping = mInputMappings.find(who);

        //whether we have yet checked the GameFramework, our fallback
        bool searchedForGameFramework = (who == GameFramework::GetSingletonPtr());

        if(inputMapping == mInputMappings.end())
        {
            //if not: are there any for the game framework?
            if(!searchedForGameFramework && (inputMapping = mInputMappings.find(GameFramework::GetSingletonPtr())) == mInputMappings.end())
            {
                //if not: return
                return;
            }
            else
            {
                searchedForGameFramework = true;
            }
        }

        //Does this key do anything?
        std::map<sf::Key::Code, InputActionButton*>::iterator action = inputMapping->second->KeyboardActions.find(keyEvent.Code);

        //if not: does it do something for the framework (provided that's not what's been checked before)
        if(!searchedForGameFramework && action == inputMapping->second->KeyboardActions.end())
        {
            inputMapping = mInputMappings.find(GameFramework::GetSingletonPtr());
            if(inputMapping == mInputMappings.end())
            {
                return;
            }
            action = inputMapping->second->KeyboardActions.find(keyEvent.Code);
        }

        if(action != inputMapping->second->KeyboardActions.end())
        {
            action->second->mIsPressed = pressed;
            if(pressed)
            {
                who->ButtonPressed(action->second);
            }
            else
            {
                who->ButtonReleased(action->second);
            }
        }
    }

    void InputManager::Unregister(InputAction* action)
    {
        std::map<InputListener*, GameInputMapping*>::iterator IMIt = mInputMappings.find(action->GetOwner());
        if(IMIt == mInputMappings.end())
        {
            return;
        }
        // Look for the action in the actions without assigned buttons
        for(std::vector<InputAction*>::iterator UAfind = IMIt->second->UnassignedActions.begin(); UAfind != IMIt->second->UnassignedActions.end(); ++UAfind)
        {
            if(*UAfind != action) continue;
            IMIt->second->UnassignedActions.erase(UAfind);
            //an action shouldn't be saved more than once
            return;
        }
        // Look for the action in the actions with assigned keyboard buttons
        for(std::map<sf::Key::Code, InputActionButton*>::iterator it = IMIt->second->KeyboardActions.begin(); it != IMIt->second->KeyboardActions.end(); ++it)
        {
            if(it->second == action)
            {
                IMIt->second->KeyboardActions.erase(it);
                //an action shouldn't be saved more than once
                return;
            }
        }
    }


    void InputManager::RegisterAction(InputActionButton* action)
    {
        GetInputMapping(action->GetOwner())->UnassignedActions.push_back(action);
    }

    void InputManager::RegisterAction(InputActionButton* action, sf::Key::Code key, const bool overwrite)
    {
        InputListener* framework = GameFramework::GetSingletonPtr();
        //check if another action from the action's game uses this key
        GameInputMapping* IM = GetInputMapping(action->GetOwner());
        std::map<sf::Key::Code, InputActionButton*>::iterator find = IM->KeyboardActions.find(key);
        if(find != IM->KeyboardActions.end())
        {
            //there is one...
            if(overwrite)
            {
                IM->UnassignedActions.push_back(find->second);
            }
            else
            {
                IM->UnassignedActions.push_back(action);
                return;
            }
        }
        //else check if a default action uses this key
        GameInputMapping* IM2 = GetInputMapping(framework);
        find = IM2->KeyboardActions.find(key);
        if(find != IM2->KeyboardActions.end())
        {
            //if so...
            if(overwrite)
            {
                IM2->UnassignedActions.push_back(find->second);
            }
            else
            {
                IM->UnassignedActions.push_back(action);
                return;
            }
        }
        //else assign this action to the key
        IM->KeyboardActions[key] = action;
    }

    InputManager::GameInputMapping* InputManager::GetInputMapping(InputListener* which)
    {
        std::map<InputListener*, GameInputMapping*>::iterator find = mInputMappings.find(which);
        if(find == mInputMappings.end())
        {
            mInputMappings[which] = new GameInputMapping;
        }
        return mInputMappings[which];
    }

} // namespace WGF
