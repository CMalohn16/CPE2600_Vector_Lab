/*
* Filename: myVector.h
* Author: Charlie Malohn
* Date: 10/1/2026
* Brief: Struct for a vector to perform operations on
*/

#pragma once

typedef struct myVector
{
    char name[100];
    float x;
    float y;
    float z;
    struct myVector *next;
} myVector;