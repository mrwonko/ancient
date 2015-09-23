#ifndef WGF_INPUTMANAGER_H
#define WGF_INPUTMANAGER_H
#include <SFML/Window/Event.hpp>
#include <map>
#include <vector>

namespace WGF
{
    class InputAction;
    class InputActionButton;
    class InputListener;
    class InputManager
    {
        public:
            /** Default constructor */
            InputManager();
            /** Default destructor */
            virtual ~InputManager();

            void Init();

            void KeyPressed (const sf::Event::KeyEvent& keyEvent);
            void KeyReleased(const sf::Event::KeyEvent& keyEvent);

            /** \brief Register an unassigned button action **/
            void RegisterAction(InputActionButton* action);
            /** \brief Register a keyboard action **/
            void RegisterAction(InputActionButton* action, sf::Key::Code key, const bool overwrite = false);

            void Unregister(InputAction* action);
        protected:
            /** \brief A struct to hold all input mappings of one game **/
            struct GameInputMapping
            {
                std::map<sf::Key::Code, InputActionButton*> KeyboardActions;
                std::vector<InputAction*> UnassignedActions;
            };
            /** Mappings for each game **/
            std::map< InputListener* , GameInputMapping* > mInputMappings;
            /** Tell game about a keypress (pressed=true) or release (pressed = false) described in keyEvent **/
            void TellAboutKeyEvent(InputListener* who, const sf::Event::KeyEvent& keyEvent, const bool pressed);
            /** Gets or creates the InputMapping for a given Game **/
            GameInputMapping* GetInputMapping(InputListener* which);
    };

} // namespace WGF

#endif // WGF_INPUTMANAGER_H
