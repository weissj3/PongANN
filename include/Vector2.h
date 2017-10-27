#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <math.h>

//This stuff Still needs testing.
//Write Unit Tests.

class Vector2
{
public:
    float x, y;

    //Add other functionality (ie. distance, project, add...)
    Vector2() { x = 0; y = 0; }
    Vector2( float X, float Y ) { x = X; y = Y; }
    
};

//Add two vectors
Vector2 operator+(const Vector2 a, const Vector2 b);

//Subtract Vector b from Vector a
Vector2 operator-(const Vector2 a, const Vector2 b);

//Negate a Vector
Vector2 operator-(const Vector2 a);

//Scale a Vector by a constant
Vector2 scaleVector2(float num, const Vector2 &v1);

//Dot two Vectors
float dotVector2(const Vector2 &v1, const Vector2 &v2);

//Find the magnitude of a vector
//To Do: Change to better method reducing chance of overflow
float magnitudeVector2(const Vector2 &v1);

//Find the Magnitude of a vector Squared
float magnitude2Vector2(const Vector2 &v1);

//Project one vector onto another
Vector2 projectVector2(Vector2 v1, Vector2 v2);

//Get the unit direction from point a to point b
Vector2 getUnitDirectionVector2(Vector2 v1, Vector2 v2);
#endif
