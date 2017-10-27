#ifndef _BALL_H_
#define _BALL_H_

#include <SDL.h>
#include "Physics.h"
#include "Vector2.h"
#include "Pong.h"

class Ball : public PhysicsObject
{
private:
    
    unsigned int m_color;
    
public:
    Ball(Vector2 pos, Vector2 vel, float rad);
    
    void Render();
    void Collision(PhysicsObject* obj);
    void setRandVel( float mag );
};

#endif
