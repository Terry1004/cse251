#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

double MAX_ANGLE = M_PI * 2;
double MAX_SPACES = 30;

void print_line(int step, double angle, double val, double derivative)
{
    printf("%3d: %5.2f ", step, angle);
    int spaces = MAX_SPACES + MAX_SPACES * val;
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }

    char ch;
    if (fabs(derivative) < 0.1)
    {
        ch = '*';
    }
    else if (derivative > 0)
    {
        ch = '\\';
    }
    else
    {
        ch = '/';
    }
    printf("%c\n", ch);
}

int main()
{
    int steps;
    while (true)
    {
        printf("Input the number of steps: ");
        scanf("%d", &steps);

        if (steps < 2)
        {
            continue;
        }
        for (int i = 0; i <= steps; i++)
        {
            double angle = (double)i / steps * MAX_ANGLE;
            double val = sin(angle);
            double derivative = cos(angle);
            print_line(i, angle, val, derivative);
        }
        return 0;
    }
}