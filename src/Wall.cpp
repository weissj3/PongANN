#include "Wall.h"
#include "Pong.h"

Wall::Wall(Vector2 pos) : PhysicsObject( true, pos, Vector2(0,0), Vector2(0,0), {Vector2(0, -10), Vector2(SCREEN_WIDTH, -10), Vector2(SCREEN_WIDTH, 0), Vector2(0, 0)} )   
{
    setType(PhysicsObject::PhysicsObjectType::WALL);
}

void Wall::Collision(PhysicsObject* obj)
{
    //Walls do not care!
    return;
}
    
