#include "InputActionButton.h"
#include "GameFramework.h"
#include "InputManager.h"

namespace WGF
{
    InputActionButton::InputActionButton(unsigned long ID, const std::string& name, const std::string& description, InputListener* owner) :
        InputAction(ID, name, description, owner),
        mIsPressed(false)
    {
        //ctor
        mType = INPUT_ACTION_BUTTON;
        GameFramework::GetSingleton().GetInputManager().RegisterAction(this);
    }

    InputActionButton::InputActionButton(unsigned long ID, const std::string& name, const std::string& description, InputListener* owner, sf::Key::Code key) :
        InputAction(ID, name, description, owner),
        mIsPressed(false)
    {
        //ctor
        mType = INPUT_ACTION_BUTTON;
        GameFramework::GetSingleton().GetInputManager().RegisterAction(this, key);
    }

    InputActionButton::~InputActionButton()
    {
        //dtor
    }

} // namespace WGF
