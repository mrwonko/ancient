#ifndef WGF_INPUTACTIONBUTTON_H
#define WGF_INPUTACTIONBUTTON_H

#include "InputAction.h"
#include "InputManager.h"

namespace WGF
{
    class InputListener;
    class InputActionButton : public WGF::InputAction
    {
        friend class InputManager;
        public:
            /** Default constructor */
            InputActionButton(unsigned long ID, const std::string& name, const std::string& description, InputListener* owner);
            InputActionButton(unsigned long ID, const std::string& name, const std::string& description, InputListener* owner, sf::Key::Code key);
            /** Default destructor */
            virtual ~InputActionButton();

            /** \brief Whether this button is currently pressed
            **/
            const bool IsPressed() {return mIsPressed;}
        protected:
            bool mIsPressed;
    };

} // namespace WGF

#endif // WGF_INPUTACTIONBUTTON_H
