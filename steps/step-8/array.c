#include <stdio.h>

/*
 * Name : Terry
 * Program to experiment with arrays
 */
#define NumMovies 10
#define MaxGrosses 5

int main()
{
    double gross[NumMovies] = {4633070, 3856195, 3171189, 1877685, 3251622,
                               3156594, 1629735, 2659234, 2028036, 510768};
    char *names[NumMovies] = {"Hall Pass", "Unknown", "I Am Number Four", "The King's Speech",
                              "Just Go With It", "Gnomeo and Juliet", "Drive Angry",
                              "Justin Beiber: Never Say Never", "Big Mommas: Like Father, Like Son",
                              "True Grit"};
    for (int i = 0; i < NumMovies; i++)
    {
        printf("Movie %2d %33s: %.0f\n", i + 1, names[i], gross[i]);
    }

    double sum = 0; /* Initialize to zero */
    for (int i = 0; i < NumMovies; i++)
    {
        sum += gross[i];
    }

    int highestGrossIndex = 0;
    double highestGross = 0;
    for (int i = 0; i < NumMovies; i++)
    {
        if (gross[i] > highestGross)
        {
            highestGrossIndex = i;
            highestGross = gross[highestGrossIndex];
        }
    }

    printf("The highest grossing film is: %s\n", names[highestGrossIndex]);

    double maxGross[MaxGrosses] = {500000, 1000000, 2000000, 4000000, 10000000};
    for (int i = 0; i < MaxGrosses; i++)
    {
        double grossCap = maxGross[i];

        int highestGrossIndex = -1;
        double highestGross = -1;
        for (int j = 0; j < NumMovies; j++)
        {
            double grossVal = gross[j];
            if (grossVal < grossCap && grossVal > highestGross)
            {
                highestGrossIndex = j;
                highestGross = grossVal;
            }
        }
        if (highestGrossIndex < 0)
        {
            printf("No film made less than %.0f\n", grossCap);
        }
        else
        {
            printf("The highest gross less than %.0f is %s at %0.f\n", grossCap, names[highestGrossIndex], highestGross);
        }
    }
}