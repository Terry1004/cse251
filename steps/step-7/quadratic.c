#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void input_quadratic_equation(double *a, double *b, double *c)
{
    printf("Input a: ");
    scanf("%lf", a);
    printf("Input b: ");
    scanf("%lf", b);
    printf("Input c: ");
    scanf("%lf", c);
}

void quadratic_equation(double a, double b, double c, double *p_z1r, double *p_z1i, double *p_z2r, double *p_z2i)
{
    double discriminant = b * b - 4 * a * c;
    if (discriminant > 0)
    {
        *p_z1r = (-b + sqrt(discriminant)) / (2 * a);
        *p_z2r = (-b - sqrt(discriminant)) / (2 * a);
        *p_z1i = 0;
        *p_z2i = 0;
    }
    else
    {
        *p_z1r = -b / (2 * a);
        *p_z2r = -b / (2 * a);
        *p_z1i = sqrt(-discriminant) / (2 * a);
        *p_z2i = -sqrt(-discriminant) / (2 * a);
    }
}

int main()
{
    /* Values for the quadratic formula */
    double a, b, c;
    double z1r, z1i; /* First zero */
    double z2r, z2i; /* Second zero */

    input_quadratic_equation(&a, &b, &c);

    quadratic_equation(a, b, c, &z1r, &z1i, &z2r, &z2i);

    /* Display the results */
    printf("Zero 1: %f + %fj\n", z1r, z1i);
    printf("Zero 2: %f + %fj\n", z2r, z2i);
}