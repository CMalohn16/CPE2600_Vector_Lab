/*
* Filename: operations.c
* Author: Charlie Malohn
* Date: 10/1/2026
* Brief: Declarations for all vector operations
*/

#include "operations.h"


void add(myVector* a, myVector* b, myVector* result)
{
    strcpy(result->name, "ans");
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
}

void sub(myVector* a, myVector* b, myVector* result)
{
    strcpy(result->name, "ans");
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
}

void mult(myVector* vector, float scalar, myVector* result)
{
    strcpy(result->name, "ans");
    result->x = vector->x * scalar;
    result->y = vector->y * scalar;
    result->z = vector->z * scalar;
}

float dot(myVector* a, myVector* b)
{
    return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

void cross(myVector* a, myVector* b, myVector* result)
{
    strcpy(result->name, "ans");
    result->x = (a->y * b->z) - (a->z * b->y);
    result->y = -((a->x * b->z) - (a->z * b->x));
    result->z = (a->x * b->y) - (a->y * b->x);
}