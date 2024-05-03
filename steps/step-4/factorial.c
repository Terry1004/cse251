#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/*
 * Simple program to experiment with looping
 */

int main()
{
    int num;
    bool done = false;

    while (!done)
    {
        printf("Number to compute the factorial of: ");
        scanf("%d", &num);

        if (num >= 0)
        {
            int fac = 1; /* Initial value of factorial */
            int f = num;
            while (f > 0)
            {
                fac = fac * f;
                f--;
            }

            printf("%d! = %d\n", num, fac);
        }
        else
        {
            done = true;
        }
    }
}