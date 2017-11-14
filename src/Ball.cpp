#include "Ball.h"
#include "Paddle.h"
#include <random>

Ball::Ball( Vector2 pos, Vector2 vel, float rad ) : PhysicsObject( true, pos, vel, Vector2( 0,0 ), std::vector <Vector2> (1, Vector2(rad, 0)))
{
    //TO DO: Maybe make the color changable
    //m_color = SDL_MapRGB( Pong::getSurface()->format, 0x00, 0x00, 0x00 );
    setType(PhysicsObject::PhysicsObjectType::BALL);
    m_roundNumber = 0;

}

void Ball::Render()
{
    // TO DO: Get width and height from Verticies
    SDL_Rect pad;
    pad.x = this->getPos().x;
    pad.y = this->getPos().y;
    pad.w = 5;
    pad.h = 5;
    
    //SDL_FillRect( Pong::getSurface(), &pad, m_color );
}

void Ball::Collision(PhysicsObject* obj)
{
    Vector2 relPosition = this->getPos() - obj->getPos(); 
    //Bounce off the Paddle
    if ( this->getCollides() && (obj->getType() == PhysicsObject::PhysicsObjectType::PADDLE))
    {
        Vector2 newVel;
        if(((Paddle*) obj)->GetId() == 1)
        {
            newVel = Vector2(abs(this->getVel().x), .75 * relPosition.y);
        }
        else
        {
            newVel = Vector2(-abs(this->getVel().x), .75 * relPosition.y);
        }
        this->setVel(newVel);
    }
    else if (this->getCollides() && (obj->getType() == PhysicsObject::PhysicsObjectType::WALL))
    {
        Vector2 vel = this->getVel();
        vel.y = -vel.y;
        this->setVel(vel);
    }
}

void Ball::setRandVel( float mag )
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0., 1.0);
    Vector2 vel;
    float randAng = dist(mt) * 1.05;
    vel.x = cos(randAng) * mag;
    vel.y = sin(randAng) * mag;
    
    if(m_roundNumber >= 5)
    {
        vel.x *= -1;
    }
    if(dist(mt) > .5)
    {
        vel.y *= -1;
    }
    m_roundNumber++;
    if(m_roundNumber == 10)
    {
        m_roundNumber = 0;
    }
    
    this->setVel(vel);
}
