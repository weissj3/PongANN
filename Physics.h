#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "Vector2.h"
#include <vector>

class PhysicsObject
{
public:
    enum PhysicsObjectType { UNKNOWN, BALL, PADDLE, WALL };
private:


    PhysicsObjectType m_type;
    Vector2 m_pos; //Defines the position of the Center of the Object
    Vector2 m_vel;
    Vector2 m_acc;
    
    bool m_collides;

    //A Vector with only one Vertex will be assume a circle where 
    //m_Verticies[0].x is the radius
    std::vector < Vector2 > m_verticies;

protected:
    void setType(PhysicsObjectType type);
    
    
public:
    
    PhysicsObject( bool collides, Vector2 pos, Vector2 vel, Vector2 acc, std::vector < Vector2 > verts );
    Vector2 getPos();
    Vector2 getVel();
    Vector2 getAcc();
    PhysicsObjectType getType();
    bool getCollides();
    const std::vector < Vector2 >* getVerts();
    bool isWithin( Vector2 point );
    void setPos( Vector2 pos );
    void setVel( Vector2 vel );
    void setAcc( Vector2 acc );
    void setVerticies( std::vector < Vector2 > verts);
    virtual void Collision(PhysicsObject* other) = 0;

};

class PhysicsHandler
{
private:
    std::vector <PhysicsObject*> m_physicsObjects;
    void CheckCollisions();

public:
    void RegisterPhysicsObject(PhysicsObject* obj);
    void DeletePhysicsObject(PhysicsObject* obj);
    void UpdatePhysics();

};

#endif
