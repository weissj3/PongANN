#include "ANNAI.h"
#include "Vector2.h"
#include "Pong.h"
#include "Ball.h"
#include <vector>

ANNAI::ANNAI(unsigned int playerNum, unsigned int n_layers, unsigned int n_nodes) : Player(playerNum), m_ANN(5, n_layers, n_nodes, 1)
{
    m_n_inputs = 5;
    m_n_layers = n_layers;
    m_n_nodes = n_nodes;
    m_n_outputs = 1;
    m_type = Player::PlayerType::ANN_AI;
}

unsigned int ANNAI::GetNumParams()
{
    return  m_n_inputs * m_n_nodes + (m_n_layers - 1) * m_n_nodes * m_n_nodes + m_n_nodes * m_n_outputs;
}

void ANNAI::Logic()
{
    //looks the same regardless of side choice
    std::vector <float> ANNinput(5);
    ANNinput[0] = abs(Pong::getBall()->getPos().x - (float)m_pad->getPos().x) / (float)SCREEN_WIDTH;
    ANNinput[1] = Pong::getBall()->getPos().y / SCREEN_HEIGHT;
    if(this->GetPlayerNumber() == 1)
    {
        ANNinput[2] = -Pong::getBall()->getVel().x / SCREEN_WIDTH;
    }
    else
    {
        ANNinput[2] = Pong::getBall()->getVel().x / SCREEN_WIDTH;
    }
    ANNinput[3] = Pong::getBall()->getVel().y / SCREEN_HEIGHT;
    ANNinput[4] = m_pad->getPos().y / SCREEN_HEIGHT;
    float result = m_ANN.Evaluate(ANNinput)[0];

    if(result < 0.0)
    {
        m_pad->StartMovingUp();
    }
    else
    {
        m_pad->StartMovingDown();
    }
}


void ANNAI::updateParameters(const Parameters &newParams)
{
    m_ANN = ANN(m_n_inputs, m_n_layers, m_n_nodes, m_n_outputs, newParams);
    m_currentParams = newParams;
}

Parameters& ANNAI::getParams()
{
    return m_currentParams;
}
