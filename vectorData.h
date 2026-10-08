/*
* Filename: vectorData.h
* Author: Charlie Malohn
* Date: 10/1/2026
* Brief: Stores an array of vectors and helper functions to access them
* Vector land. Home of the vectors
*/

#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "myVector.h"
#include "operations.h"

#define NUM_VECTORS 10

static const char ops[6] = {'+', '-', '*', '.', 'x', '\0'};

static myVector vectors[NUM_VECTORS];
static myVector errorVec;

void printVector(myVector* vector);
myVector* getVector(char name[]);
void store(myVector* vector);
void clearStorage();
void displayHelp();
void list();
void performOperation(char op, const char *a, const char *b, myVector *outputVec);
void assign(myVector *vector, const char *xTok, const char *yTok, const char *zTok);
bool tokenToFloat(const char *token, float *num);
