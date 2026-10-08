/*
* Filename: vectorData.c
* Author: Charlie Malohn
* Date: 10/1/2026
* Brief: Stores an array of vectors and helper functions to access them
*/

#include "vectorData.h"

void printVector(myVector* vector)
{
    printf("%s = <%.3f, %.3f, %.3f>\n", vector->name, vector->x, vector->y, vector->z);
}

myVector* getVector(char name[])
{
    printf("Getting Vector %s\n", name);
    for (int i = 0; i < NUM_VECTORS; i++)
    {
        if (!strcmp(vectors[i].name, name))
        {
            return &(vectors[i]);
        }
    }
    printf("Unable to find vector %s\n", name);
    strcpy(errorVec.name, "ERROR|Vector not found");
    return &errorVec;
}

void store(myVector* vector)
{
    bool done = false;
    for (int i = 0; i < NUM_VECTORS && !done; i++)
    {
        if (!*(vectors[i].name) || !strcmp(vectors[i].name, vector->name))
        {
            vectors[i] = *vector;
            done = true;
        }
        if (i == NUM_VECTORS - 1)
        {
            printf("Out of space. Run \"clear\" to clear vector storage");
            return;
        }
    }
    printf("Storing Vector %s as ", vector->name);
    printVector(vector);
}

void clearStorage()
{
    printf("Clearing Vector Storage\n");
    myVector emptyVec;
    strcpy(emptyVec.name, "");
    for (int i = 0; i < NUM_VECTORS; i++)
    {
        vectors[i] = emptyVec;
    }
}

void displayHelp()
{
    printf("  help -> Display this guide\n");
    printf("  quit/exit -> Close the program\n");
    printf("  list -> List all stored vectors (up to 10)\n");
    printf("  clear -> Clear all stored vectors\n\n");
}

void list()
{
    printf("Listing vectors\n");
    for (int i = 0; i < NUM_VECTORS; i++)
    {
        if (*(vectors[i].name))
        {
            printVector(&(vectors[i]));
        }
    }
}

void performOperation(char op, const char *a, const char *b, myVector *outputVec)
{
    //Be sure to check for invalid operation (mostly "")
    //So do a switch case with default case being error
    printf("Performing Operation %c\n", op);

    myVector vecA;
    myVector vecB;
    myVector scaledVector;
    vecA = *(getVector((char*)a));
    vecB = *(getVector((char*)b));
    float scalar;
    float *scalar_ptr = &scalar;

    if (strstr(vecA.name, "ERROR"))
    {
        if (!tokenToFloat(a, scalar_ptr))
        {
            printf("%s\n", vecA.name);
            return;
        }
        scaledVector = vecB;
    }
    if (strstr(vecB.name, "ERROR"))
    {
        if (!tokenToFloat(b, scalar_ptr))
        {
            printf("%s\n", vecA.name);
            return;
        }
        scaledVector = vecA;
    }
    switch(op) 
    {
        case '+':
            add(&vecA, &vecB, outputVec);
            break;
        case '-':
            sub(&vecA, &vecB, outputVec);
            break;
        case '*':
            mult(&scaledVector, scalar, outputVec);
            break;
        case 'x':
            cross(&vecA, &vecB, outputVec);
            break;
        default:
            printf("Invlaid operation: %c\n", op);
            strcpy(outputVec->name, "ERROR|Invalid operation");
    }
}

void assign(myVector *vector, const char *xTok, const char *yTok, const char *zTok) 
{
    float xNew, yNew, zNew;
    float *xNewPtr = &xNew;
    float *yNewPtr = &yNew;
    float *zNewPtr = &zNew;
    if (tokenToFloat(xTok, xNewPtr) && tokenToFloat(yTok, yNewPtr) && tokenToFloat(zTok, zNewPtr))
    {
        vector->x = *xNewPtr;
        vector->y = *yNewPtr;
        vector->z = *zNewPtr;
    }
    else
    {
        strcpy(vector->name, "ERROR|Invalid float");
    }
}

/**
* @brief Converts a string to a float
* @param token The string to convert to a float
* @param num pointer to a float representing the result
* @return True if the conversion was successful and 
            false if the string does not represent a float
 */
bool tokenToFloat(const char *token, float *num)
{
    char *endptr;
    *num = strtof(token, &endptr);
    if (token == endptr)
    {
        return false;
    }
    return true;
}
