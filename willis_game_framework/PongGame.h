#ifndef PONGGAME_H
#define PONGGAME_H

#include "WGF/Game.h"

namespace WGF
{
    //Forward declarations so we can use pointers to undeclared classes
    class Sprite;
}

/** \brief An example game that shows how to use the game interface

By no means an example of clean programming, wasn't planned at all so it's rather messy but it should be clear how to use everything from this example. **/
class PongGame : public WGF::Game
{
    public:
        /** Default constructor */
        PongGame();
        /** Default destructor */
        virtual ~PongGame();

        virtual void ButtonPressed(WGF::InputActionButton* button);

        virtual bool Init();

        virtual bool Deinit();

        virtual void Update(float time);
    private:
        enum PongActions
        {
            ACT_LEFTUP = ACT_COMMONACTION_LAST,
            ACT_LEFTDOWN
        };

        WGF::Sprite *mBall, *mLeftPaddle, *mRightPaddle;

        bool mBallGoLeft;
        int mLeftPaddleMultY;
        int mRightPaddleMultY;

        const float mBallSpeedX;
        float mBallSpeedY;
        unsigned int mPointsLeft, mPointsRight;

        void ResetBall();
        void BallYMove(float time);
};

#endif // PONGGAME_H
