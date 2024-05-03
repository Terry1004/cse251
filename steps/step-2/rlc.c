#include <stdio.h>
#include <math.h>

int main()
{
    double capacitance, inductance;
    printf("Input Capacitance (microfarads): ");
    scanf("%lf", &capacitance);
    printf("Input Inductance (millihenrys): ");
    scanf("%lf", &inductance);

    capacitance = capacitance / 1e6;
    inductance = inductance / 1e3;

    double frequency = 1 / (sqrt(capacitance * inductance) * 2 * M_PI);
    printf("Resonant Frequency is %.3lf\n", frequency);
}