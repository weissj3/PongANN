#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Paddle.h"
#include "Pong.h"



class Player 
{
public:
enum PlayerType { UNKNOWN, HUMAN, BASICAI, ANN_AI };
private:
    unsigned int m_score;
    unsigned int m_playerNumber;
    
protected:

    PlayerType m_type;
    Paddle* m_pad;
    virtual void Logic() = 0;

public:

    Player(unsigned int playerNum);
    ~Player();
    
    Paddle* GetPaddle() { return m_pad; }
    unsigned int GetScore() { return m_score; }
    unsigned int GetPlayerNumber() { return m_playerNumber; }
    PlayerType GetType() { return m_type; }
    void ScorePoint() { ++m_score; }
    void Update();
    void ResetPaddle();
    void ResetScore() { m_score = 0; }
    


};

#endif
