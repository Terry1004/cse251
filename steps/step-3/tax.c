#include <stdio.h>
#include <stdlib.h>

int main()
{
    double income;
    printf("Enter your annual income: ");
    scanf("%lf", &income);

    double tax = 0;
    if (income < 9350)
    {
        printf("%.2lf\n", tax);
        return 0;
    }

    int status, dependents, deduction;
    printf("What is your filing status?\n");
    printf("1) single\n");
    printf("2) married filing jointly\n");
    printf("3) married filing separately\n");
    printf("Please enter a number: ");
    scanf("%d", &status);
    switch (status)
    {
    case 1:
    case 3:
        dependents = 1;
        deduction = 5700;
        break;
    case 2:
        deduction = 11400;
        printf("How many children do you have? ");
        scanf("%d", &dependents);
        dependents += 2;
        break;
    }
    deduction += dependents * 3650;

    double taxable = income - deduction;
    if (taxable <= 16750)
    {
        tax = 0.1 * taxable;
    }
    else if (taxable <= 68000)
    {
        tax = 1675 + 0.15 * (taxable - 16750);
    }
    else if (taxable <= 137300)
    {
        tax = 9362.5 + 0.25 * (taxable - 68000);
    }
    else
    {
        tax = 26687.5 + 0.28 * (taxable - 137300);
    }
    printf("%.2lf\n", tax);
}