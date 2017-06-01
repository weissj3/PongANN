#include "Ball.h"

Ball::Ball( Vector2 pos, Vector2 vel, float rad ) : PhysicsObject( true, pos, vel, Vector2( 0,0 ), std::vector <Vector2> (1, Vector2(rad, 0)))
{
    //TO DO: Maybe make the color changable
    m_color = SDL_MapRGB( Pong::getSurface()->format, 0x00, 0x00, 0x00 );
    setType(PhysicsObject::PhysicsObjectType::BALL);

}

void Ball::Render()
{
    // TO DO: Get width and height from Verticies
    SDL_Rect pad;
    pad.x = this->getPos().x;
    pad.y = this->getPos().y;
    pad.w = 5;
    pad.h = 5;
    
    SDL_FillRect( Pong::getSurface(), &pad, m_color );
}

void Ball::Collision(PhysicsObject* obj)
{
    Vector2 relPosition = this->getPos() - obj->getPos(); 
    //Bounce off the Paddle
    if ( this->getCollides() && (obj->getType() == PhysicsObject::PhysicsObjectType::PADDLE))
    {
        Vector2 newVel(- this->getVel().x, .75 * relPosition.y);
        
        this->setVel(newVel);
    }
    else if (this->getCollides() && (obj->getType() == PhysicsObject::PhysicsObjectType::WALL))
    {
        Vector2 vel = this->getVel();
        vel.y = -vel.y;
        this->setVel(vel);
    }
}
