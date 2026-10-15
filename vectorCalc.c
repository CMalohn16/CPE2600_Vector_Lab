/*
* Filename: vectorCalc.c
* Author: Charlie Malohn
* Date: 10/12/2026
* Brief: Main vector calculator program
* Compile with make
*/

#include "vectorData.h"
#include "fileIO.h"

#define MAX_INPUT_LENGTH 50

int main(void)
{

    bool running = true;

    char input[MAX_INPUT_LENGTH];
    char *token1;
    char *token2;
    char *token3;
    char *token4;
    char *token5;

    do {
        printf("\nEnter an operation to perform or \"help\" for a list of options\n");
        printf("VectorCalc> ");
        fgets(input, MAX_INPUT_LENGTH, stdin);

        //Tokenize input changing any nonexistent tokens to ""
        //-----------------------------------------------------------------------------
        int numTokens = 0;
        token1 = strtok(input, " ,\n");
        if (token1)
        {
            numTokens++;
            token1[strlen(token1)] = '\0';
        }
        else
        {
            token1 = "";
        }
        token2 = strtok(NULL, " ,\n");
        if (token2)
        {
            numTokens++;
            token2[strlen(token2)] = '\0';
        }
        else
        {
            token2 = "";
        }
        token3 = strtok(NULL, " ,\n");
        if (token3)
        {
            numTokens++;
            token3[strlen(token3)] = '\0';
        }
        else
        {
            token3 = "";
        }
        token4 = strtok(NULL, " ,\n");
        if (token4)
        {            
            numTokens++;
            token4[strlen(token4)] = '\0';
        }
        else
        {
            token4 = "";
        }
        token5 = strtok(NULL, " ,\n");
        if (token5)
        {
            numTokens++;
            token5[strlen(token5)] = '\0';
        }
        else
        {
            token5 = "";
        }

        //Parse input
        //----------------------------------------------------------------------

        myVector result;
        
        //Basic one token commands
        if (!strcmp(token1, "quit") || !strcmp(token1, "exit"))
        {
            running = false;
        }
        else if (!strcmp(token1, "help"))
        {
            displayHelp();
        }
        else if (!strcmp(token1, "list"))
        {
            list();
        }
        else if (!strcmp(token1, "clear"))
        {
            clearStorage();
        }
        else if (!strcmp(token1, "load"))
        {
            int error = loadFromCSV(token2);
            if (error < 0)
            {
                printf("Failed to open file %s", token2);
            }
            else if (error)
            {
                printf("Skipping %d vectors because of formatting issues\n", error);
            }
        }
        else if (numTokens == 1)
        {
            //If only one token is present and it is not a command, display that vector
            myVector *result_ptr = &result;
            result_ptr = getVector(token1);
            if (strstr(result_ptr->name, "ERROR"))
            {
                printf("%s\n", result_ptr->name);
            }
            else
            {
                printVector(result_ptr);
            }
        }
        else
        {
            char token2Char = *token2;
            //If token2 is an operation, do the math and display the answer
            if (strchr(ops, token2Char))
            {
                //Special case for dot product
                if (token2Char == '.')
                {
                    myVector dotVecA;
                    myVector dotVecB;
                    dotVecA = *(getVector(token1));
                    dotVecB = *(getVector(token3));
                    if (strstr(dotVecA.name, "ERROR"))
                    {
                        printf("%s\n", dotVecA.name);
                    }
                    else if (strstr(dotVecB.name, "ERROR"))
                    {
                        printf("%s\n", dotVecB.name);
                    }
                    else
                    {
                        printf("ans = %f\n", dot(&dotVecA, &dotVecB));
                    }
                }
                else //Default case
                {
                    performOperation(token2Char, token1, token3, &result);
                    if (strstr(result.name, "ERROR"))
                    {
                        printf("%s\n", result.name);
                    }
                    else
                    {
                        printVector(&result);
                    }
                }
            }
            else if (token2Char == '=') //If token2 is =, assign a value
            {
                if (strstr(token1, "ERROR")) 
                {
                    printf("Vector name cannot contain \"ERROR\"\n");
                }
                else 
                {
                    strcpy(result.name, token1);
                    char token4Char = *token4;
                    if (numTokens == 3)
                    {
                        result = *(getVector(token3));
                    } 
                    else if (strchr(ops, token4Char))
                    {
                        performOperation(token4Char, token3, token5, &result);
                    }
                    else
                    {
                        assign(&result, token3, token4, token5);
                    }

                    //Check for any errors and don't assign a vector if an error is present
                    if (strstr(result.name, "ERROR"))
                    {
                        printf("%s", result.name);
                        printf("\nCanceling assignment\n");
                    }
                    else
                    {
                        strcpy(result.name, token1);
                        store(&result);
                        printVector(getVector(token1));
                    }
                }
            }
            else
            {
                printf("Invalid Command\n");
            }
        }

    } while (running);
    return 0;
}