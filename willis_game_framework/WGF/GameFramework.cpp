#include "GameFramework.h"
#include "Logfile.h"
#include "Game.h"
#include "Configfile.h"
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include "InputManager.h"
#include "ImageManager.h"
#include "Game.h"

namespace WGF
{

    GameFramework::GameFramework(const std::string& configfilename, const std::string& logfilename) :
        mRunning(false),
        mLogfile(new Logfile(logfilename)),
        mCurrentGame(NULL),
        mConfig(new Configfile),
        mConfigfilename(configfilename),
        mWindow(NULL),
        mInputManager(new InputManager),
        mImageManager(new ImageManager)
    {
        mLogfile->Log("Willi's Game Framework greets the World: \"Hello World!\"");
        mInputManager->Init();
        //ctor
        mLogfile->Empty();

        mConfig->LoadFromFile(mConfigfilename);

    }

    GameFramework::~GameFramework()
    {
        //dtor
        mLogfile->Log("Willi's Game Framework is about to leave you!");
        mLogfile->Log("- deleting Framework-Config");
        delete mConfig;
        mLogfile->Log("- deleting InputManager");
        delete mInputManager;
        mLogfile->Log("- deleting ImageManager");
        delete mImageManager;
        //delete logfile
        mLogfile->Log("- closing logfile");
        mLogfile->Log("Willi's Game Framework out");
        delete mLogfile;
    }

    void GameFramework::AddGame(Game* game)
    {
        std::string logme = "Willi's Game Framework greets the game ";
        logme += game->GetName();
        logme += "!";
        mLogfile->Log(logme);
        //does a game with this name already exist?
        if(mGames.find(game->GetName()) != mGames.end())
        {
            //if so: is it the same game?
            if(mGames[game->GetName()] == game)
            {
                //if so: ignore, we already have this, but log it.
                std::string error = "ERROR: tried to add the game ";
                error += game->GetName();
                error += " multiple times! Game not added another time.";
                mLogfile->Log(error);
            }
            else
            {
                //else: rename the game

                //new name
                std::string name;
                //add a number at the end and increase it until a game with this name does not yet exist
                unsigned int number = 2;
                do
                {
                    std::stringstream ss;
                    ss << game->GetName() << " " << number;
                    name = ss.str();
                    //Is this the same as this already existing renamed game?
                    if( (mGames.find(name)->second) == game)
                    {
                        //log error and return
                        std::string error = "ERROR: tried to add the game ";
                        error += game->GetName();
                        error += " multiple times, yet there's another game with the same name hence the first time this game has been renamed. Please double-check your code!";
                        mLogfile->Log(error);
                        return;
                    }
                }
                while(mGames.find(name) != mGames.end());
                //log error
                std::string error = "ERROR: tried to add multiple (different) games of the name ";
                error += game->GetName();
                error += " - renaming the ones added later.";
                mLogfile->Log(error);

                //once found: add this game
                mGames[name] = game;
            }
        }
        else //no game of this name exists yet
        {
            mGames[game->GetName()] = game;
        }
    }

    void GameFramework::ButtonPressed(InputActionButton* bt)
    {
        switch(bt->GetID())
        {
            case Game::ACT_STOP:
                if(mCurrentGame == NULL) mRunning = false;
                break;
            //TODO menu up/down etc.
            default:
                break;
        }
    }

    void GameFramework::Start()
    {
        mLogfile->Log("Willi's Game Framework is now running!");
        mRunning = true;
        while(mRunning)
        {
            //Main Loop
            //TODO main loop
            HandleEvents();
            if(mCurrentGame)
            {
                mCurrentGame->Update(mWindow->GetFrameTime());
            }
        }
        mLogfile->Log("Willi's Game Framework has stopped running!");
        Deinit();
    }

    void GameFramework::HandleEvents()
    {
        sf::Event event;
        while(mWindow->GetEvent(event))
        {
            switch(event.Type)
            {
                case sf::Event::Closed:
                    mRunning = false;
                    break;
                case sf::Event::KeyPressed:
                    mInputManager->KeyPressed(event.Key);
                    break;
                case sf::Event::KeyReleased:
                    mInputManager->KeyReleased(event.Key);
                    break;
                //TODO more events
                default:
                    break;
            }
        }
    }

    bool GameFramework::Init()
    {
        mLogfile->Log("Willi's Game Framework is initializing...");
        unsigned long style = sf::Style::Resize | sf::Style::Close;
        if(mConfig->GetInt("fullscreen", 0))
        {
            style |= sf::Style::Fullscreen;
        }
        sf::VideoMode videoMode(mConfig->GetInt("width", 800), mConfig->GetInt("height", 600), mConfig->GetInt("bits", 32));
        if(!videoMode.IsValid())
        {
            mLogfile->Log("ERROR: Invalid Video Mode (resolution or bpp)");
            return false;
        }
        mLogfile->Log("- Render Window created");
        mWindow = new sf::RenderWindow(videoMode, "Willis Game Framework", style );
        mWindow->Clear();
        mWindow->Display();
        mLogfile->Log("Willi's Game Framework is initialized!");
        return true;
    }

    void GameFramework::Deinit()
    {
        mLogfile->Log("Willi's Game Framework is deinitializing...");
        //TODO deinit()
        //end current game
        //delete games
        mLogfile->Log("- clearing game list");
        for(std::map<std::string, Game*>::iterator it = mGames.begin(); it != mGames.end(); ++it)
        {
            delete it->second;
        }
        //close window
        mLogfile->Log("- closing window");
        delete mWindow;
        mLogfile->Log("Willi's Game Framework is deinitialized!");
    }

    void GameFramework::FatalError(const std::string& errorMessage)
    {
        std::string log = "FATAL ERROR: ";
        log += errorMessage;
        //TODO: visual error message
        mLogfile->Log(log);
        mRunning = false;
    }

    bool GameFramework::StopGame(Game* game)
    {
        if(mCurrentGame == game)
        {
            if(mCurrentGame == NULL)
            {
                return true;
            }
            mCurrentGame = NULL;
            mLogfile->Log(std::string("Willi's Game Framework stops the game ")+game->GetName()+"!");

            //If the game doesn't shut down properly we have a problem. A big one. We can't be sure if it can be started again, so we abandon the whole framework and run away, far away.
            if(!game->Init(false))
            {
                std::string error = "Game \"";
                error += game->GetName();
                error += "\" could not Deinitialize properly. Gameframework must be restarted.";
                FatalError(error);
                return false;
            }
            return true;
        }
        return false;
    }

    void GameFramework::StartGame(Game* game)
    {
        //game already running?
        if(mCurrentGame == game)
        {
            return;
        }
        //stop whatever game is currently running
        if(!StopGame(mCurrentGame))
        {
            //problem? game framework needs to shut down then. don't start the new game.
            return;
        }
        //new game in the framework yet?
        bool found = false;
        for(std::map<std::string, Game*>::iterator it = mGames.begin(); it != mGames.end(); ++it)
        {
            if(it->second == game)
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            //no? add it.
            AddGame(game);
        }
        //start it.
        if(!game->Init(true))
        {
            //initialization went wrong and nobody knows how exactly. we don't want to risk anything so let's just kill the whole framework.
            std::string error = "couldn't initialize ";
            error += game->GetName();
            error += "!";
            FatalError(error);
            return;
        }
        mLogfile->Log(std::string("Willi's Game Framework starts the game ")+game->GetName()+"!");
        mCurrentGame = game;
    }

    template<> GameFramework* GX::Singleton<GameFramework>::ms_Singleton = NULL;

} // namespace WGF
