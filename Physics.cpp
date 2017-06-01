#include "Physics.h"
#include <iostream>

PhysicsObject::PhysicsObject( bool collides, Vector2 pos, Vector2 vel, Vector2 acc, std::vector < Vector2 > verts )
{
    m_pos = pos;
    m_vel = vel;
    m_acc = acc;
    m_collides = collides;
    
    m_verticies = verts;
    m_type = PhysicsObject::PhysicsObjectType::UNKNOWN;

}

bool PhysicsObject::getCollides()
{
    return m_collides;
}

Vector2 PhysicsObject::getPos()
{
    return m_pos;
}

Vector2 PhysicsObject::getVel()
{
    return m_vel;
}

Vector2 PhysicsObject::getAcc()
{
    return m_acc;
}

PhysicsObject::PhysicsObjectType PhysicsObject::getType()
{
    return m_type;
}

const std::vector < Vector2 >* PhysicsObject::getVerts()
{
    return &m_verticies;
}

bool PhysicsObject::isWithin( Vector2 point )
{
    Vector2 relPoint = point - m_pos;
    switch(m_verticies.size())
    {
        case 1:
            return (m_verticies[0].x > magnitudeVector2(relPoint));
            break;
        case 4:
            return (m_verticies[0].x < relPoint.x && m_verticies[2].x > relPoint.x && m_verticies[0].y < relPoint.y && m_verticies[2].y > relPoint.y);
            break;
        default:
            std::cerr << "Unrecognized shape" << std::endl;
            break;
    }
    return false;
}
void PhysicsObject::setPos( Vector2 pos )
{
    m_pos = pos;
}

void PhysicsObject::setVel( Vector2 vel )
{
    m_vel = vel;
}

void PhysicsObject::setAcc( Vector2 acc )
{
    m_acc = acc;
}

void PhysicsObject::setType(PhysicsObject::PhysicsObjectType type)
{
    m_type = type;
}

void PhysicsObject::setVerticies( std::vector < Vector2 > verts )
{
    m_verticies = verts;
}


void PhysicsHandler::RegisterPhysicsObject(PhysicsObject* obj)
{
    m_physicsObjects.push_back(obj);

}
void PhysicsHandler::UpdatePhysics()
{
    for(int i = 0; i < m_physicsObjects.size(); ++i)
    {
        PhysicsObject* currentObj = m_physicsObjects[i];
        currentObj->setVel(currentObj->getVel() + scaleVector2(0.5, currentObj->getAcc()));
    }
    //Number of steps per physics step to improve collision detection
    int numSteps = 20;
    for(int j = 0; j < numSteps; ++j)
    {
        for(int i = 0; i < m_physicsObjects.size(); ++i)
        {
            PhysicsObject* currentObj = m_physicsObjects[i];
            currentObj->setPos(currentObj->getPos() + scaleVector2((1.0/(float)numSteps), currentObj->getVel()));
            CheckCollisions();
        }
    }
    for(int i = 0; i < m_physicsObjects.size(); ++i)
    {
        PhysicsObject* currentObj = m_physicsObjects[i];
        currentObj->setVel(currentObj->getVel() + scaleVector2(0.5, currentObj->getAcc()));
    }        

}

void PhysicsHandler::CheckCollisions()
{
    for(int i = 0; i < m_physicsObjects.size(); ++i)
    {
        PhysicsObject* currentObj = m_physicsObjects[i];
        for(int j = 0; j < m_physicsObjects.size(); ++j)
        {
            if( i != j )
            {
                PhysicsObject* compareObj = m_physicsObjects[j];
                const std::vector <Vector2> *compVerts = compareObj->getVerts();
                if( compVerts->size() == 4 )
                {
                    for( int k = 0; k < compVerts->size(); ++k)
                    {
                        if(currentObj->isWithin((*compVerts)[k] + compareObj->getPos()))
                        {
                            currentObj->Collision(compareObj);
                            compareObj->Collision(currentObj);
                        }
                    }
                }
                else
                {
                    //Calculate edge point for circle in 
                    //direction of current object.
                    //See if it is within the current object
                    if(currentObj->isWithin(scaleVector2((*compVerts)[0].x, getUnitDirectionVector2(compareObj->getPos(), currentObj->getPos())) + compareObj->getPos()))
                    {
                        currentObj->Collision(compareObj);
                        compareObj->Collision(currentObj);
                    }
                }
            }
        }
    }
}

void PhysicsHandler::DeletePhysicsObject(PhysicsObject* obj)
{
    for(  std::vector<PhysicsObject*>::iterator i = m_physicsObjects.begin(); i != m_physicsObjects.end(); i++)
    {
        if (*i == obj)
        {
            m_physicsObjects.erase(i);
            break;
        }
    }
}









