#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "transistors.h"

bool InputContinueOpt(char* prompt);

/*
 * Name :  Terry
 * Description : Simple transistor description example program
 */

int main()
{
    int i;
    Tran *trans;
    int numTrans = 0;

    printf("transistors!\n");

    /* Allocate space for one transistor */
    trans = malloc(sizeof(Tran));
    numTrans = 0;

    do {
        /* Input the transistor */
        trans[numTrans++] = InputTransistor();

        /* Increase the space by one transistor */
        trans = realloc(trans, sizeof(Tran) * (numTrans+1));
    } while(InputContinueOpt("Would you like to enter another transistor (Y/N)? "));

    /* Output the transistors */
    printf("\nThe transistors:\n");
    for (i = 0; i < numTrans; i++)
    {
        DisplayTransistor(trans[i]);
    }

    /* Free the memory */
    free(trans);
}

bool InputContinueOpt(char* prompt)
{
    char buffer[100];
    bool valid = false;
    bool cont;

    do {
        printf("%s", prompt);
        /* Get a line of up to 100 characters */
        fgets(buffer, sizeof(buffer), stdin);

        /* Remove any \n we may have input */
        if (strlen(buffer) > 0)
            buffer[strlen(buffer) - 1] = '\0';
        
        if (strcmp(buffer, "y") == 0 || strcmp(buffer, "Y") == 0)
        {
            valid = true;
            cont = true;
        }
        else if (strcmp(buffer, "n") == 0 || strcmp(buffer, "N") == 0)
        {
            valid = true;
            cont = false;
        }
    } while (!valid);

    return cont;
}