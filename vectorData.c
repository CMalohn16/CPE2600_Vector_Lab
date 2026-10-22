/*
* Filename: vectorData.c
* Author: Charlie Malohn
* Date: 10/12/2026
* Brief: Stores an array of vectors and helper functions to access them
*/

#include "vectorData.h"

static myVector *head;
static myVector errorVec;

/**
 * Prints a vector to the console
 */
void printVector(myVector* vector)
{
    printf("%s = <%.3f, %.3f, %.3f>\n", vector->name, vector->x, vector->y, vector->z);
}

/**
 * Gets a stored vector address
 * @param name The name of the vector to look for
 * @return A pointer to the vector with a matching name
 *         Returns a vector with an ERROR message if a vector is not found
 */
myVector* getVector(char name[])
{
    if (!strcmp(name, ""))
    {
        strcpy(errorVec.name, "ERROR|Vector \"\" not found");
        return &errorVec;
    }
    myVector *currentVector = head;
    
    while (currentVector)
    {
        if (!strcmp(currentVector->name, name))
        {
            return currentVector;
        }
        currentVector = currentVector->next;
    }
    sprintf(errorVec.name, "ERROR|Vector \"%s\" not found", name);
    return &errorVec;
}

/**
 * @brief Adds a vector to the linked list of stored vectors
 * @param vector Address of the vector to store
 */
void store(myVector* vector)
{
    //Set aside some memory for the new vector
    myVector *vecPtr = malloc(sizeof(myVector));
    //Copy data to be stored into the new memory location
    memcpy(vecPtr, vector, sizeof(myVector));
    vecPtr->next = NULL;
    if (!head)
    {
        //If the head is not assigned set it to the new vector
        head = vecPtr;
        return;
    }
    myVector *currentVector = head;
    while (currentVector)
    {
        if (!strcmp(currentVector->name, vecPtr->name))
        {
            //Updating an existing vector since the names match
            myVector *nextAddress = currentVector->next;
            //Copy the contents of the new pointer into the new memory location
            memcpy(currentVector, vecPtr, sizeof(myVector));
            free(vecPtr);
            //This new vector still needs to point to the next one in the linked list
            currentVector->next = nextAddress;
            return;
        }
        if (!currentVector->next)
        {
            //Since the end of the list has been reached and no vector with the
            //given name exists, add the new vector to the end
            currentVector->next = vecPtr;
            return;
        }
        currentVector = currentVector->next;
    }
}

/**
 * @brief Removes all stored vectors and frees all allocated memory
 */
void clearStorage()
{
    myVector *currentVector = head;
    myVector *addr;
    while (currentVector)
    {
        addr = currentVector;
        currentVector = currentVector->next;
        free(addr);
    }
    head = NULL;
}

/**
 * @brief Displays a help menu for the user
 */
void displayHelp()
{
    printf("  help -> Display this guide\n");
    printf("  quit/exit -> Close the program\n");
    printf("  list -> List all stored vectors (up to 10)\n");
    printf("  clear -> Clear all stored vectors\n");
    printf("  fill <uint16_t num> -> Creates \"num\" new random vectors\n");
    printf("  load <filename> loads from a csv file\n\n");
}

/**
 * @brief Lists out all vectors currently in storage
 */
void list()
{
    printf("Listing vectors: \n");

    myVector *currentVector = head;
    while(currentVector)
    {
        if (*(currentVector->name))
        {
            printVector(currentVector);
        }
        currentVector = currentVector->next;
    }
}

/**
 * @brief Adds random vectors to storage
 * @param num Number of vectors to store
 */
void fill(int num)
{
    myVector *fillVecPtr = malloc(sizeof(myVector));
    char name[sizeof(int) * 2 + 1];
    for (int i = 0; i < num; i++)
    {
        name[0] = '\0';
        generateName(i, name);
        strcpy(fillVecPtr->name, name);
        fillVecPtr->x = rand() % 100;
        fillVecPtr->y = rand() % 100;
        fillVecPtr->z = rand() % 100;
        store(fillVecPtr);
    }
    free(fillVecPtr);
}

/**
 * @brief Generates a name for a random vector from the fill() function
 * @param index number to convert to vector name
 * @param name Pointer to the where the name should be stored
 * @return vector name
 */
void generateName(int index, char name[])
{
    index++;
    bool started = false;
    int mask;
    for (int i = sizeof(int) * 2 - 1; i >= 0; i--)
    {
        mask = 0xF << (i * 4);
        if ((mask & index) > 0)
        {
            started = true;
        }
        if (started)
        {
            int len = strlen(name);
            name[len] = (char)(((mask & index) >> (i * 4)) + 97);
            name[len + 1] = '\0';
        }
    }
}


/**
 * @brief Performs the vector operation passed in
 * @param op operation to perform
 * @param a string representing the first operand
 * @param b string representing the second operand
 * @param outputVec vector pointer to store the result in
 */
void performOperation(char op, const char *a, const char *b, myVector *outputVec)
{
    //Special case for scalar multiplication
    if (op == '*')
    {
        float scalar;
        float *scalar_ptr = &scalar;
        myVector scaledVector;
        if (tokenToFloat(a, scalar_ptr))
        {
            scaledVector = *(getVector((char*)b));
            if (strstr(scaledVector.name, "ERROR"))
            {
                strcpy(outputVec->name, scaledVector.name);
                return;
            }
        } 
        else if (tokenToFloat(b, scalar_ptr))
        {
            scaledVector = *(getVector((char*)a));
            if (strstr(scaledVector.name, "ERROR"))
            {
                strcpy(outputVec->name, scaledVector.name);
                return;
            }
        } 
        else
        {
            strcpy(outputVec->name, "ERROR|One of the operands must be a scalar");
            return;
        }
        mult(&scaledVector, *scalar_ptr, outputVec);
        return;
    }

    //Other operations
    myVector vecA;
    myVector vecB;
    vecA = *(getVector((char*)a));
    vecB = *(getVector((char*)b));

    if (strstr(vecA.name, "ERROR"))
    {
        strcpy(outputVec->name, vecA.name);
        return;
    }
    if (strstr(vecB.name, "ERROR"))
    {
        strcpy(outputVec->name, vecB.name);
        return;
    }
    switch(op) 
    {
        case '+':
            add(&vecA, &vecB, outputVec);
            break;
        case '-':
            sub(&vecA, &vecB, outputVec);
            break;
        case 'x':
            cross(&vecA, &vecB, outputVec);
            break;
        case '.':
            strcpy(outputVec->name, "ERROR|Cannot assign dot product to a vector");
            break;
        default:
            strcpy(outputVec->name, "ERROR|Invalid operation");
    }
}

/**
 * @brief Assigns given values to a vector
 * @param vector Pointer to the vector to assign
 * @param xTok String containing x value
 * @param yTok Stirng containing y value
 * @param zTok String containing z value
 */
void assign(myVector *vector, const char *xTok, const char *yTok, const char *zTok) 
{
    if (!xTok || !yTok || !zTok)
    {
        strcpy(vector->name, "ERROR|Invalid float");
        return;
    }
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
