#ifndef _BASICAI_H_
#define _BASICAI_H_
#include "Player.h"

class BasicAI : public Player
{
private:

    float m_difficulty;
    void Logic();

public:
    BasicAI(float difficulty, unsigned int playerNum);

};

#endif
