#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double TOLERANCE = 1e-10;
const int MIN_N = 10;
const int MAX_N = 1e5;

double integrate(double a, double b, int n)
{
    double delta = (b - a) / n;
    double integral = 0;
    for (int i = 1; i <= n; i++)
    {
        double point = a + (i - 0.5) * delta;
        if (point == 0)
        {
            integral += delta;
        }
        else
        {
            integral += delta * sin(M_PI * point) / (M_PI * point);
        }
    }
    return integral;
}

int main()
{
    double a, b;
    printf("Enter a value for a: ");
    scanf("%lf", &a);
    printf("Enter a value for b: ");
    scanf("%lf", &b);
    printf("Integral evaluation\n");

    double last_integral = integrate(a, b, MIN_N);
    printf("%d %.9lf\n", MIN_N, last_integral);
    for (int n = MIN_N + 1; n < MAX_N; n++)
    {
        double integral = integrate(a, b, n);
        double err = fabs(integral - last_integral);
        printf("%d %.9lf %.3e\n", n, integral, err);

        if (err < TOLERANCE)
        {
            printf("The integral result is %.9lf\n", integral);
            return 0;
        }
        last_integral = integral;
    }
}