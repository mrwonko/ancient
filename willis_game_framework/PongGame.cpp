#include "PongGame.h"
//We need to include this here because the forward declaration just told the compiler that there is such a class, not how it can be used.
#include "WGF/InputActionButton.h"
#include "WGF/Sprite.h"

#include <iostream>
#include <stdexcept>

PongGame::PongGame() :
    WGF::Game("Pong"),
    mBallGoLeft(false),
    mBallSpeedX(200)
{
    //ctor
    mInputActions.push_back(new WGF::InputActionButton(ACT_LEFTUP, "Linker Spieler Hoch", "bewegt den Schlaeger des linken Spielers hoch", this, sf::Key::W));
    mInputActions.push_back(new WGF::InputActionButton(ACT_LEFTDOWN, "Linker Spieler Runter", "bewegt den Schlaeger des linken Spielers runter", this, sf::Key::S));
}

PongGame::~PongGame()
{
    //dtor
}

void PongGame::ButtonPressed(WGF::InputActionButton* button)
{
    switch(button->GetID())
    {
        case ACT_STOP:
            Stop();
            break;
        default:
            break;
    }
}

bool PongGame::Init()
{
    //will throw if the file does not exist
    try
    {
        mBall = new WGF::Sprite("Data/Pong/ball.png");
        mLeftPaddle = new WGF::Sprite("Data/Pong/paddle.png");
        mRightPaddle = new WGF::Sprite("Data/Pong/paddle.png");
        mPointsLeft = mPointsRight = 0;
        ResetBall();
        mRightPaddle->SetX(mRenderWindow.GetWidth()-mRightPaddle->GetSize().x);
        mRightPaddle->SetY(mRenderWindow.GetHeight()/2-mRightPaddle->GetSize().y/2);
        mLeftPaddle->SetY(mRenderWindow.GetHeight()/2-mLeftPaddle->GetSize().y/2);
    }
    catch(...)
    {
        //error output should already be done, just return false.
        return false;
    }
    return true;
}

bool PongGame::Deinit()
{
    delete mBall;
    delete mLeftPaddle;
    delete mRightPaddle;
    return true;
}

void PongGame::ResetBall()
{
    mBall->SetPosition(mRenderWindow.GetWidth() / 2 - mBall->GetSize().x/2, mRenderWindow.GetHeight() / 2 - mBall->GetSize().y/2);
    mBallSpeedY = sf::Randomizer::Random(-1*mBallSpeedX, mBallSpeedX);
}

void PongGame::Update(float time)
{
    if(mBallGoLeft)
    {
        mBall->SetX(mBall->GetPosition().x - mBallSpeedX*time);
        BallYMove(time);

        if(mBall->GetPosition().x < mLeftPaddle->GetSize().x)
        {
            mBallGoLeft = false;

            float lowestBallPoint = mBall->GetPosition().y+mBall->GetSize().y;
            float highestBallPoint = mBall->GetPosition().y;
            float lowestPaddlePoint = mLeftPaddle->GetPosition().y + mLeftPaddle->GetSize().y;
            float highestPaddlePoint = mLeftPaddle->GetPosition().y;

            //paddle missed
            if(lowestBallPoint < highestPaddlePoint || highestBallPoint > lowestPaddlePoint)
            {
                mPointsRight += 1;
                ResetBall();
            }
        }
    }
    else
    {
        mBall->SetX(mBall->GetPosition().x + mBallSpeedX*time);
        BallYMove(time);
        if(mBall->GetPosition().x > mRenderWindow.GetWidth() - mBall->GetSize().x - mRightPaddle->GetSize().x)
        {
            mBallGoLeft = true;

            float lowestBallPoint = mBall->GetPosition().y+mBall->GetSize().y;
            float highestBallPoint = mBall->GetPosition().y;
            float lowestPaddlePoint = mRightPaddle->GetPosition().y + mRightPaddle->GetSize().y;
            float highestPaddlePoint = mRightPaddle->GetPosition().y;

            //paddle missed
            if(lowestBallPoint < highestPaddlePoint || highestBallPoint > lowestPaddlePoint)
            {
                mPointsLeft += 1;
                ResetBall();
            }
        }
    }
    if(IsPressed(ACT_LEFTUP) && mLeftPaddle->GetPosition().y > 0)
    {
        mLeftPaddle->SetY(mLeftPaddle->GetPosition().y - mBallSpeedX * time);
    }
    else if(IsPressed(ACT_LEFTDOWN) && mLeftPaddle->GetPosition().y < mRenderWindow.GetHeight() - mLeftPaddle->GetSize().y)
    {
        mLeftPaddle->SetY(mLeftPaddle->GetPosition().y + mBallSpeedX * time);
    }
    if(IsPressed(ACT_UP) && mRightPaddle->GetPosition().y > 0)
    {
        mRightPaddle->SetY(mRightPaddle->GetPosition().y - mBallSpeedX * time);
    }
    else if(IsPressed(ACT_DOWN) && mRightPaddle->GetPosition().y < mRenderWindow.GetHeight() - mRightPaddle->GetSize().y)
    {
        mRightPaddle->SetY(mRightPaddle->GetPosition().y + mBallSpeedX * time);
    }
    mRenderWindow.Clear();
    mRenderWindow.Draw(*mBall);
    mRenderWindow.Draw(*mLeftPaddle);
    mRenderWindow.Draw(*mRightPaddle);
    mRenderWindow.Display();
}

void PongGame::BallYMove(float time)
{
    mBall->SetY(mBall->GetPosition().y + mBallSpeedY*time);
    //Hit upper end and moving up
    if(mBall->GetPosition().y < 0 && mBallSpeedY < 0
    //Hit lower end and moving down
    || mBall->GetPosition().y > mRenderWindow.GetHeight()-mBall->GetSize().y && mBallSpeedY > 0)
    {
        mBallSpeedY *= -1;
    }
}
