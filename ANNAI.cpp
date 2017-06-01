#include "ANNAI.h"
#include "Vector2.h"
#include "Pong.h"
#include "Ball.h"
#include <vector>

ANNAI::ANNAI(unsigned int playerNum, unsigned int n_layers, unsigned int n_nodes) : Player(playerNum), m_ANN(n_layers, n_nodes, 1)
{
    m_type = Player::PlayerType::ANN_AI;
}

void ANNAI::Logic()
{
    std::vector <float> ANNinput(5);
    ANNinput[0] = Pong::getBall()->getPos().x / SCREEN_WIDTH;
    ANNinput[1] = Pong::getBall()->getPos().y / SCREEN_HEIGHT;
    ANNinput[2] = Pong::getBall()->getVel().x / SCREEN_WIDTH;
    ANNinput[3] = Pong::getBall()->getVel().y / SCREEN_HEIGHT;
    ANNinput[4] = m_pad->getPos().y / SCREEN_HEIGHT;
    float result = m_ANN.Evaluate(ANNinput)[0];
    if(result < .5)
    {
        m_pad->StartMovingUp();
    }
    else
    {
        m_pad->StartMovingDown();
    }
}
