#include <stdio.h>
#include <math.h>
#include <stdbool.h>

double START_ALTITUDE = 100; /* Meters */
double START_VELOCITY = 0;   /* Meters per second */
double START_FUEL = 100;     /* Kilograms */
double POWER = 1.5;          /* Acceleration per kilogram of fuel */
double G = -1.63;            /* Moon gravity in m/s^2 */
double MAX_BURN = 5;         /* Max fuel that can be burned */

double parse_burn(double fuel)
{
    double burn;
    bool valid = false;
    do
    {
        printf("How much fuel would you like to burn: ");
        scanf("%lf", &burn);
        if (burn < 0)
        {
            printf("You can't burn negative fuel\n");
        }
        else if (burn > fuel)
        {
            printf("You can't burn fuel you don't have\n");
        }
        else if (burn > MAX_BURN)
        {
            printf("You can't burn more than 5 kilograms per second\n");
        }
        else
        {
            printf("Burning %.1lf kilograms of fuel\n", burn);
            valid = true;
        }
    } while (!valid);
    return burn;
}

/*
 * Simple lunar lander program.
 * By:  Terry
 */

int main()
{
    printf("Lunar Lander - (c) 2012, by Terry\n");

    double altitude = START_ALTITUDE;
    double velocity = START_VELOCITY;
    double fuel = START_FUEL;

    printf("Altitude: %.2lf\n", altitude);
    printf("Velocity: %.2lf\n", velocity);
    printf("You have %.1lf kilograms of fuel\n", fuel);

    int seconds = 0;
    while (altitude > 0)
    {
        printf("Altitude: %.2f\n", altitude);
        printf("Velocity: %.2f\n", velocity);
        printf("You have %.1f kilograms of fuel\n", fuel);

        double burn = parse_burn(fuel);
        velocity = velocity + G + POWER * burn;
        altitude += velocity;
        fuel -= burn;
        seconds++;
    }

    printf("You landed with a velocity of %.2lf\n", velocity);
    printf("You landed in %d seconds\n", seconds);
    printf("Your remaining fuel is %.1lf\n", fuel);
    if (fabs(velocity) > 3)
    {
        printf("Your next of kin have been notified\n");
    }
}
