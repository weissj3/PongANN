#include "Paddle.h"
#include "Pong.h"

Paddle::Paddle(int id, Vector2 pos) : PhysicsObject( true, pos, Vector2(0,0), Vector2(0,0), {Vector2(-5, -20), Vector2(5, -20), Vector2(5, 20), Vector2(-5, 20)} )   
{
    m_id = id;
    //TO DO: Maybe make the color changable
    m_color = SDL_MapRGB( Pong::getSurface()->format, 0x00, 0x00, 0x00 );
    setType(PhysicsObject::PhysicsObjectType::PADDLE);
}


void Paddle::Render()
{
    // TO DO: Get width and height from Verticies
    SDL_Rect pad;
    if( !this->getVerts()->size() )
    {
        return;
    }
    pad.x = this->getPos().x + (*(this->getVerts()))[0].x;
    pad.y = this->getPos().y + (*(this->getVerts()))[0].y;
    pad.w = 10;
    pad.h = 40;
    
    SDL_FillRect( Pong::getSurface(), &pad, m_color );
}

void Paddle::StartMovingUp()
{
    this->setVel(Vector2(0, -8));
}

void Paddle::StopMovingUp()
{
    if( this->getVel().y < 0 )
    {
        this->setVel(Vector2(0,0));
    }
}

void Paddle::StartMovingDown()
{
    this->setVel(Vector2(0, 8));
}
void Paddle::StopMovingDown()
{
    if( this->getVel().y > 0 )
    {
        this->setVel(Vector2(0,0));
    }
}

void Paddle::Collision(PhysicsObject* obj)
{
    if( this->getCollides() && (obj->getType() == PhysicsObject::PhysicsObjectType::WALL) )
    {
        this->setPos(this->getPos() - this->getVel());
        this->setVel(Vector2(0,0));
    }
}
