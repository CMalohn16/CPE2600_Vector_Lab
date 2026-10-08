/*
* Filename: operations.h
* Author: Charlie Malohn
* Date: 10/1/2026
* Brief: Functions to perform on vectors while using vector calculator
*/

#pragma once

#include "myVector.h"
#include <string.h>

void add(myVector* a, myVector* b, myVector* result);
void sub(myVector* a, myVector* b, myVector* result);
void mult(myVector* vector, float scalar, myVector* result);
float dot(myVector* a, myVector* b);
void cross(myVector* a, myVector* b, myVector* result);

