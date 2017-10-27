#ifndef _HUMAN_PLAYER_H_
#define _HUMAN_PLAYER_H_
#include "Player.h"


class HumanPlayer : public Player
{
private:

    void Logic();

public:
    HumanPlayer(unsigned int playerNum);
    
    void KeyUp( int key );
    void KeyDown( int Key );

};

#endif
