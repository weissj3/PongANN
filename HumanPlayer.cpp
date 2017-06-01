#include "HumanPlayer.h"
#include "Pong.h"

HumanPlayer::HumanPlayer(unsigned int playerNum) : Player(playerNum)
{
    
    m_type = HUMAN;
    
}


void HumanPlayer::Logic()
{
    //Human Players do not have any AI
}

void HumanPlayer::KeyDown( int key )
{
    switch(key)
    {
        case SDLK_w:
            m_pad->StartMovingUp();
            break;
        case SDLK_s:
            m_pad->StartMovingDown();
            break;    
        default:
            break;
    }
}

void HumanPlayer::KeyUp( int key )
{
    switch(key)
    {
        case SDLK_w:
            m_pad->StopMovingUp();
            break;
        case SDLK_s:
            m_pad->StopMovingDown();
            break;    
        default:
            break;
    }
}
