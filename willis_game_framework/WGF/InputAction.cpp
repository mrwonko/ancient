#include "InputAction.h"
#include "GameFramework.h"
#include "InputManager.h"

namespace WGF
{

    InputAction::InputAction(unsigned int ID, const std::string& name, const std::string& description, InputListener* owner) :
        mType(INPUT_ACTION),
        mID(ID),
        mName(name),
        mDescription(description),
        mOwner(owner)
    {
        //ctor
    }

    InputAction::~InputAction()
    {
        //dtor
        GameFramework::GetSingleton().GetInputManager().Unregister(this);
    }

} // namespace WGF
