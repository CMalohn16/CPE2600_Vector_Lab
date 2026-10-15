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
    printf("Loading from file %s\n", filename);
    FILE *file_ptr = fopen(filename, "r");

    if (file_ptr == NULL)
    {
        return -1;
    }

    int numErrors = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file_ptr) != NULL)
    {
        printf("%s", line);
    }

    return numErrors;
}