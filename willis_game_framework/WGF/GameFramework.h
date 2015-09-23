#ifndef WGF_GAMEFRAMEWORK_H
#define WGF_GAMEFRAMEWORK_H

#include "GxSingleton.h"
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "InputListener.h"

/** For the lazy ones: short way of logging something Framework-related **/
#define WGF_LOG(x); GameFramework::GetSingleton().GetLogfile().Log(x);

//Forward declarations
namespace sf
{
    class RenderWindow;
}

namespace WGF
{
    //Forward declarations
    class Game;
    class Logfile;
    class Configfile;
    class InputManager;
    class ImageManager;
    /** A simple framework for multiple (mini?-)games

    First, create on GameFramework object. Then Add all your Games via AddGame(), finally Start().
    **/
    class GameFramework : public GX::Singleton<GameFramework>, public InputListener
    {
        public:
            /** Default constructor */
            GameFramework(const std::string& configfilename="framework.cfg", const std::string& logfilename="log_framework.txt");
            /** Default destructor */
            virtual ~GameFramework();

            /** Returns a reference to the Logfile **/
            Logfile& GetLogfile() const { assert(mLogfile); return *mLogfile; }

            /** Add a game to the framework **/
            void AddGame(Game* game);

            /** Starts the framework, opens main menu **/
            void Start();

            /** A fatal error that makes it necessary to shut the Framework down **/
            void FatalError(const std::string& errorMessage);

            /** Stop the given game if it's currently running
            \return Whether the Game was stopped, i.e. if it was running and shut down properly **/
            bool StopGame(Game* game);

            Game* GetCurrentGame() {return mCurrentGame;}
            InputManager& GetInputManager() {return *mInputManager;}
            ImageManager& GetImageManager() {return *mImageManager;}

            virtual void ButtonPressed(InputActionButton* bt);

            //TODO make private once menu exists
            /** \brief adds the game if necessary and starts it
            \note this is going to be no longer available to the public as soon as the framework's got a menu to select the game to start and will only be used internally then
            **/
            void StartGame(Game* game);

            /** \brief Gives you a reference to the Render Window so you can draw stuff on it **/
            sf::RenderWindow& GetRenderWindow() { return *mWindow;}

            //TODO make private again and call from Start() once game selection works
            /** Initializes the Framework
            \return success **/
            bool Init();

        protected:

            /** Deinitializes the Framework **/
            void Deinit();

            /** uhm... handles events :-P **/
            void HandleEvents();

            /** whether the Framework is still running **/
            bool mRunning;

            /** the log file **/
            Logfile* mLogfile;
            /** all the (mini-)games this framework has, where each game is mapped to its name **/
            std::map<std::string, Game*> mGames;
            Game* mCurrentGame;

            /** Game config - e.g. resolution is saved here. **/
            Configfile* mConfig;
            /** Name of the config file **/
            const std::string mConfigfilename;

            /** Application Window **/
            sf::RenderWindow* mWindow;

            InputManager* mInputManager;

            ImageManager* mImageManager;
    };

} // namespace WGF

#endif // WGF_GAMEFRAMEWORK_H
