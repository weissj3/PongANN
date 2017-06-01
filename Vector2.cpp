#include "Vector2.h"

Vector2 operator-(const Vector2 a, const Vector2 b)
{
    return Vector2(a.x - b.x, a.y - b.y);
}


Vector2 operator-(const Vector2 a)
{
    return Vector2(-a.x, -a.y);
}

//Add two vectors
Vector2 operator+(const Vector2 a, const Vector2 b)
{
    return Vector2(a.x + b.x, a.y + b.y);
}

//Scale a Vector by a constant
Vector2 scaleVector2(float num, const Vector2 &v1)
{
    return Vector2(v1.x * num, v1.y * num);
}

//Dot two Vectors
float dotVector2(const Vector2 &v1, const Vector2 &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

//Find the magnitude of a vector
float magnitudeVector2(const Vector2 &v1)
{
    return sqrt(v1.x * v1.x + v1.y * v1.y);
}

//Find the Magnitude of a vector Squared
float magnitude2Vector2(const Vector2 &v1)
{
    return v1.x * v1.x + v1.y * v1.y;
}

//Project one vector onto another
//Check this function
Vector2 projectVector2(Vector2 v1, Vector2 v2)
{
    return scaleVector2(dotVector2(v1, v2)/magnitude2Vector2(v1), v2);
}

//Get unit direction from point a to point b
Vector2 getUnitDirectionVector2(Vector2 v1, Vector2 v2)
{
    //Check to make sure we do no return nan
    //Instead return 0 vector which while not normalized will not nan
    if ( magnitudeVector2(v2 - v1) != 0 )
    {
        return scaleVector2(1.0 / magnitudeVector2(v2 - v1), (v2 - v1));
    }
    return Vector2(0,0);
}
