#include "Player.h"

Player::Player(unsigned int playerNum)
{
    m_playerNumber = playerNum;
    if(playerNum == 1)
    {
        m_pad = new Paddle(Vector2(10, 240));
    }
    else
    {
        m_pad = new Paddle(Vector2(630, 240));
    }
    Pong::getPhysicsHandler()->RegisterPhysicsObject( (PhysicsObject*) m_pad);
    m_type = UNKNOWN;
}

Player::~Player()
{
    Pong::getPhysicsHandler()->DeletePhysicsObject( (PhysicsObject*) &m_pad);
    delete m_pad;
}

void Player::Update()
{
    Logic();
    m_pad->Render();
}

void Player::ResetPaddle()
{
    if(m_playerNumber == 1)
    {
        m_pad->setPos(Vector2(10, 240));
    }
    else
    {
        m_pad->setPos(Vector2(630, 240));
    }
}
