#include "BasicAI.h"
#include "Ball.h"
#include "Pong.h"


BasicAI::BasicAI(float difficulty, unsigned int playerNum) : Player(playerNum)
{
    m_type = Player::PlayerType::BASICAI;
    m_difficulty = difficulty;
}

void BasicAI::Logic()
{
    Vector2 BallPosition = Pong::getBall()->getPos();
    if(BallPosition.x / SCREEN_WIDTH < m_difficulty)
    {
        if(BallPosition.y > m_pad->getPos().y)
        {
            m_pad->StartMovingDown();
        }
        else
        {
            m_pad->StartMovingUp();
        }
    }
    else
    {
        m_pad->StopMovingUp();
    }
}
