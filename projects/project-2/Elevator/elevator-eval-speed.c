#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "ElevatorLib.h"

#define KP 600
#define KI 1
#define KD 8
#define DT 0.001
#define MaxLoad 7
#define Level1 0
#define Level3 (2 * FloorSpacing)
#define BrakeDistance (FloorSpacing / 2)

typedef struct
{
    double kp;
    double ki;
    double kd;
    double dt;

    double errorSum;
    double lastError;
} PIDController;

typedef struct
{
    double speedUpSum;
    double speedUpCount;
    double speedDownSum;
    double speedDownCount;
    double speedMax;

    double speedUpMax;
    double speedDownMax;
} EvalRecord;

double ComputePower(PIDController *controller, double desired, double current)
{
    double error = desired - current;
    double errorSum = controller->errorSum + error;
    double errorDiff = error - controller->lastError;

    double power = controller->kp * error + controller->ki * errorSum * controller->dt + controller->kd * errorDiff / controller->dt;

    controller->errorSum = errorSum;
    controller->lastError = error;
    // printf("error: %lf, errorSum: %lf, errorDiff: %lf, power: %lf\n", error, errorSum, errorDiff, power);

    return power;
}

void UpdateEvalRecord(EvalRecord records[], int load, double position, bool goingUp, double speed)
{
    EvalRecord *record = records + load;
    bool fullSpeed = position < Level3 - BrakeDistance && position > Level1 + BrakeDistance;
    if (goingUp && fullSpeed)
    {
        record->speedUpSum += speed;
        record->speedUpCount++;
        if (fabs(speed) > fabs(record->speedUpMax))
        {
            record->speedUpMax = speed;
        }
    }
    else if (!goingUp && fullSpeed)
    {
        record->speedDownSum += speed;
        record->speedDownCount++;
        if (fabs(speed) > fabs(record->speedDownMax))
        {
            record->speedDownMax = speed;
        }
    }
    if (fabs(speed) > fabs(record->speedMax))
    {
        record->speedMax = speed;
    }
}

void EvalSingleRecord(EvalRecord record, char prefix[])
{
    double avgUp = record.speedUpSum / record.speedUpCount;
    double avgDown = record.speedDownSum / record.speedDownCount;
    printf("[%s] Average speed up: %lf\n", prefix, avgUp);
    printf("[%s] Average speed down: %lf\n", prefix, avgDown);
    printf("[%s] Maximum speed: %lf\n", prefix, record.speedMax);

    double maxAvgError = fmax(fabs(avgUp - 1), fabs(avgDown + 1));
    double maxMaxError = fmax(fabs(record.speedMax) - fabs(avgUp), fabs(record.speedMax) - fabs(avgDown));
    printf("[%s] Result: %lf\n", prefix, maxAvgError * maxMaxError);

    printf("[%s] Maximum speed up: %lf\n", prefix, record.speedUpMax);
    printf("[%s] Maximum speed down: %lf\n", prefix, record.speedDownMax);
    printf("\n");
}

void Eval(EvalRecord records[], int size)
{
    EvalRecord total = {0};

    for (int i = 0; i < size; i++)
    {
        EvalRecord record = records[i];

        char prefix[7];
        snprintf(prefix, sizeof prefix, "load=%d", i);
        EvalSingleRecord(record, prefix);

        total.speedUpSum += record.speedUpSum;
        total.speedUpCount += record.speedUpCount;
        total.speedDownSum += record.speedDownSum;
        total.speedDownCount += record.speedDownCount;
        if (fabs(record.speedMax) > fabs(total.speedMax))
        {
            total.speedMax = record.speedMax;
        }
        if (fabs(record.speedUpMax) > fabs(total.speedUpMax))
        {
            total.speedUpMax = record.speedUpMax;
        }
        if (fabs(record.speedDownMax) > fabs(total.speedDownMax))
        {
            total.speedDownMax = record.speedDownMax;
        }
    }

    EvalSingleRecord(total, "total");
}

/*
 * Name :        Terry
 * Description : Project 2 - The elevator controller
 */

/*
 * Name :        main()
 * Description : Program entry point.
 */
int main()
{
    /*
     * This call starts the elevator system running
     */
    printf("Elevator Startup\n");
    ElevatorStartup();

    PIDController controller = {KP, KI, KD, DT, 0, 0};
    EvalRecord records[MaxLoad + 1] = {0};

    SetBrake(false);
    bool goingUp = true;
    double desiredSpeed = 1;

    int load = 0;
    SetLoading(load);

    /*
     * This loop runs until we shut the elevator system down
     * by closing the window it runs in.
     */
    while (IsElevatorRunning())
    {
        if (load > MaxLoad)
        {
            break;
        }

        double position = GetPosition();
        if (goingUp && position > Level3 - FloorTolerance)
        {
            /* We are above the third floor. Reverse direction */
            goingUp = false;
            desiredSpeed = -1;
            SetLoading(load);
        }
        else if (goingUp && position > Level3 - BrakeDistance)
        {
            desiredSpeed = fmax((Level3 - position) / BrakeDistance, 0);
        }
        else if (!goingUp && position < FloorTolerance)
        {
            /* We are below the first floor. Reverse direction */
            goingUp = true;
            desiredSpeed = 1;
            load++;
            SetLoading(load);
        }
        else if (!goingUp && position < Level1 + BrakeDistance)
        {
            desiredSpeed = fmin((Level1 - position) / BrakeDistance, 0);
        }

        double currentSpeed = GetVelocity();
        double power = ComputePower(&controller, desiredSpeed, currentSpeed);
        // printf("position: %lf, desiredSpeed: %lf, currentSpeed: %lf\n", position, desiredSpeed, currentSpeed);
        SetMotorPower(power);

        UpdateEvalRecord(records, load, position, goingUp, currentSpeed);
    }

    Eval(records, MaxLoad + 1);

    /*
     * This call shuts down the elevator system
     */
    printf("Elevator Shutdown\n");
    ElevatorShutdown();
    return 0;
}
