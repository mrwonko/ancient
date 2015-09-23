#ifndef WGF_GAME_H
#define WGF_GAME_H

#include <string>
#include <vector>
#include <map>
#include "GameFramework.h"
#include "InputActionButton.h"
#include <SFML/Graphics.hpp>

namespace WGF
{
    //Forward declarations
    class InputAction;
    /** Interface for games **/
    class Game : public InputListener
    {
        friend class InputManager;
        public:
            /** \brief Default constructor */
            Game(const std::string& name);
            /** \brief Default destructor */
            virtual ~Game();
            /** \brief Returns this game's name **/
            const std::string& GetName() const { return mName; }
            /** \brief Called every frame so the game can go on
            \param time time since last frame in ms **/
            virtual void Update(float time) {}

            /** \brief used only internally, use Init() and Deinit()

            Called by the framework, does some initializing/deinitializing and then calls Init() or Deinit() which you can (and should) overwrite **/
            bool Init(bool init);

            /** Basic common input actions (mostly buttons, e.g. on keyboard) every game may use
            \note your Custom Actions should start with ACT_COMMONACTION_LAST or actions will be mixed **/
            enum CommonAction
            {
                //button presses
                ACT_UP,
                ACT_DOWN,
                ACT_LEFT,
                ACT_RIGHT,
                ACT_ATTACK,
                ACT_ATTACK2,
                ACT_USE,
                ACT_JUMP,
                ACT_ITEM1,
                ACT_ITEM2,
                ACT_ITEM3,
                ACT_ITEM4,
                ACT_ITEM5,
                ACT_ITEM6,
                ACT_ITEM7,
                ACT_ITEM8,
                ACT_ITEM9,
                ACT_ITEM10,
                ACT_PAUSE,
                ACT_STOP,

                ACT_COMMONACTION_LAST //Make sure your own enums start with this so action IDs don't overlap
            };
        protected:
            /** \brief Once the game is started this is used to initialize it
            \return whether initialization was successfull and the game can be started **/
            virtual bool Init() {return true;}
            /** \brief Once the game is stopped this is used to deinitialize it
            \return whether deinitialization was successfull **/
            virtual bool Deinit() {return true;}
            /** \brief To stop the game and return to the menu **/
            void Stop();
            /** \brief This game's name **/
            const std::string mName;
            /** \brief all the game's unique input actions

            put your input actions in here **/
            std::vector<InputAction*> mInputActions;

            /** \brief The sf::RenderWindow in which you render **/
            sf::RenderWindow& mRenderWindow;

            /** \brief Whether the button of the given action ID (CommonAction or your own) is pressed

            Your actions need to be in mInputActions or they won't be checked for
            \return whether the given key is pressed or false if none is found **/
            bool IsPressed(unsigned long act_ID);
        private:
            static std::vector<InputActionButton*> mCommonButtonActions;
    };

} // namespace WGF

#endif // WGF_GAME_H
