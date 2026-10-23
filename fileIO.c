/*********************************************************
 * File: fileIO.c
 * Name: Charlie Malohn
 * Date: 10/15/2026
 * Brief: Defines functions to interact with files
 **********************************************************/

#include "fileIO.h"

/**
 * @brief Loads all correctly formatted vectors from a CSV file into vector storage
 * @param filename Name of the file to read from
 * @return An error code if something went wrong
 *          -1: Unable to open file
 *          else: number of vectors skipped for formatting errors
 */
int loadFromCSV(char *filename)
{
    FILE *file_ptr = fopen(filename, "r");

    if (file_ptr == NULL)
    {
        return -1;
    }

    int numErrors = 0;
    char line[MAX_LINE_LENGTH];
    myVector result;

    while (fgets(line, MAX_LINE_LENGTH, file_ptr) != NULL)
    {
        char *name;
        char *xTok;
        char *yTok;
        char *zTok;

        name = strtok(line, ",\r\n");
        if (name)
        {
            name[strlen(name)] = '\0';
        }
        xTok = strtok(NULL, ",\r\n");
        if (xTok)
        {
            xTok[strlen(xTok)] = '\0';
        }
        yTok = strtok(NULL, ",\r\n");
        if (yTok)
        {
            yTok[strlen(yTok)] = '\0';
        }
        zTok = strtok(NULL, ",\r\n");
        if (zTok)
        {
            zTok[strlen(zTok)] = '\0';
        }

        strcpy(result.name, name);
        assign(&result, xTok, yTok, zTok);

        if (strstr(result.name, "ERROR"))
        {
            strcpy(result.name, "");
            numErrors++;
        }
        else
        {
            store(&result);
        }
    }

    fclose(file_ptr);

    return numErrors;
}

/**
 * @brief Saves all stored vectors to a csv file
 * @param filename Name of the file to save the vectors in
 * @return 0 when executed successfully
 */
int saveToCSV(char *filename)
{
    FILE *file_ptr = fopen(filename, "w");
    
    myVector *currentVector = getHead();
    while(currentVector)
    {
        fprintf(file_ptr, "%s,%f,%f,%f\n", 
            currentVector->name, 
            currentVector->x, 
            currentVector->y, 
            currentVector->z
        );
        currentVector = currentVector->next;
    }

    fclose(file_ptr);
    return 0;
}
