#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "Physics.h"
#include <SDL.h>

class Paddle : public PhysicsObject
{
private:

    Uint32 m_color;


public:
    
    Paddle(Vector2 pos);
    
    void StartMovingUp();
    void StopMovingUp();
    void StartMovingDown();
    void StopMovingDown();
    
    void Render();
    void Collision(PhysicsObject* obj);

};

#endif
