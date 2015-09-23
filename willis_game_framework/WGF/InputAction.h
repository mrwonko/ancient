#ifndef WGF_INPUTACTION_H
#define WGF_INPUTACTION_H

#include <string>

#include <SFML/Window/Event.hpp>

namespace WGF
{
    class InputListener;
    /** \brief input from the user

    Instead of sending the game keystrokes the game tells the framework what actions it knows (like move forward, shoot, ...) and then the game handles custom key settings and sends the game the action the user wants to perform.
    **/
    //TODO InputManager
    class InputAction
    {
        public:
            //joystick buttons only have an ID - what to do?
            //create a input thing class?
            /** Default destructor */
            virtual ~InputAction();
            const unsigned int GetID() const { return mID;}
            const std::string& GetName() const{ return mName;}
            const std::string& GetDescription() const{ return mDescription;}
            ///Which game this action belongs to
            ///\return pointer to the game or NULL for common actions
            InputListener * GetOwner() const{ return mOwner;}

            enum InputActionType
            {
                INPUT_ACTION,
                INPUT_ACTION_BUTTON,
                INPUT_ACTION_AXIS
            };
            InputActionType GetType() { return mType;}
        protected:
            /** Create an input action with an ID, a name, a description and its game
            **/
            InputAction(unsigned int ID, const std::string& name, const std::string& description, InputListener* owner);
            InputActionType mType;
        private:
            unsigned int mID;
            /** \brief Name of the Action

            like forward **/
            const std::string mName;
            /** \brief Description of the Action

            like move forward **/
            const std::string mDescription;

            ///which game this action is from (NULL=common)
            InputListener * const mOwner;
    };

} // namespace WGF

#endif // WGF_INPUTACTION_H
