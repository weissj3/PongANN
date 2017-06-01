#ifndef _WALL_H_
#define _WALL_H_


#include "Physics.h"

class Wall : public PhysicsObject
{

public:
    Wall(Vector2 pos);
    void Collision(PhysicsObject* obj);


};

#endif
