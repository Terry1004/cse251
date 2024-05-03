#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "ElevatorLib.h"

#define KP 600
#define KI 1
#define KD 8
#define DT 0.001
#define UpSpeed 1
#define DownSpeed -1
#define BrakeDistance (FloorSpacing / 2)
#define DoorOpenTime 3
#define NoFloorAvailable -1
#define NumFloors 3

typedef struct
{
    double kp;
    double ki;
    double kd;
    double dt;

    double errorSum;
    double lastError;
} PIDController;

typedef enum
{
    Idle,
    Moving,
    OpenDoor,
    ClosingDoor,
} ElevatorState;

typedef enum
{
    GoingUp,
    GoingDown,
} Direction;

typedef struct
{
    ElevatorState state;
    Direction direction;
    PIDController *controller;
    int nextFloor;
} Elevator;

typedef enum
{
    Equal,
    AboveBrake,
    AboveWithinBrake,
    BelowBrake,
    BelowWithinBrake,
} ReletivePosition;

double ComputePower(PIDController *controller, double desired, double current);
void MoveTo(int floor, ReletivePosition relativePos, PIDController *controller);
bool IsUp(Direction dir);
Direction ReverseDirection(Direction dir);
ReletivePosition WhereIs(int floor);
bool IsAbove(ReletivePosition pos);
bool IsBelow(ReletivePosition pos);
int FurthestFloorWithOppLight(Direction dir);

void StateIdle(Elevator *elevator);
void StateMoving(Elevator *elevator);
void StateOpenDoor(Elevator *elevator);
void StateClosingDoor(Elevator *elevator);

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
    Elevator elevator = {Idle, GoingUp, &controller, NoFloorAvailable};

    /*
     * This loop runs until we shut the elevator system down
     * by closing the window it runs in.
     */
    while (IsElevatorRunning())
    {
        switch (elevator.state)
        {
        case Idle:
            StateIdle(&elevator);
            break;
        case Moving:
            StateMoving(&elevator);
            break;
        case OpenDoor:
            StateOpenDoor(&elevator);
            break;
        case ClosingDoor:
            StateClosingDoor(&elevator);
            break;
        }
    }

    /*
     * This call shuts down the elevator system
     */
    printf("Elevator Shutdown\n");
    ElevatorShutdown();
    return 0;
}

double ComputePower(PIDController *controller, double desired, double current)
{
    double error = desired - current;
    double errorSum = controller->errorSum + error;
    double errorDiff = error - controller->lastError;

    double power = controller->kp * error + controller->ki * errorSum * controller->dt + controller->kd * errorDiff / controller->dt;

    controller->errorSum = errorSum;
    controller->lastError = error;

    return power;
}

void MoveTo(int floor, ReletivePosition relativePos, PIDController *controller)
{
    double position = GetPosition();
    double currentSpeed = GetVelocity();
    double targetPosition = (floor - 1) * FloorSpacing;

    double desiredSpeed;

    switch (relativePos)
    {
    case AboveBrake:
        desiredSpeed = UpSpeed;
        break;
    case AboveWithinBrake:
        desiredSpeed = fmax((targetPosition - position) / BrakeDistance, 0);
        break;
    case BelowBrake:
        desiredSpeed = DownSpeed;
        break;
    case BelowWithinBrake:
        desiredSpeed = fmin((targetPosition - position) / BrakeDistance, 0);
        break;
    }
    SetMotorPower(ComputePower(controller, desiredSpeed, currentSpeed));
}

bool IsUp(Direction dir)
{
    switch (dir)
    {
    case GoingUp:
        return true;
    case GoingDown:
        return false;
    }
}

Direction ReverseDirection(Direction dir)
{
    switch (dir)
    {
    case GoingUp:
        return GoingDown;
    case GoingDown:
        return GoingUp;
    }
}

ReletivePosition WhereIs(int floor)
{
    double position = GetPosition();
    if (position > (floor - 1) * FloorSpacing + BrakeDistance)
    {
        return BelowBrake;
    }
    else if (position > (floor - 1) * FloorSpacing + FloorTolerance)
    {
        return BelowWithinBrake;
    }
    else if (position < (floor - 1) * FloorSpacing - BrakeDistance)
    {
        return AboveBrake;
    }
    else if (position < (floor - 1) * FloorSpacing - FloorTolerance)
    {
        return AboveWithinBrake;
    }
    else
    {
        return Equal;
    }
}

bool IsAbove(ReletivePosition pos)
{
    if (pos == AboveWithinBrake || pos == AboveBrake)
    {
        return true;
    }
    return false;
}

bool IsBelow(ReletivePosition pos)
{
    if (pos == BelowWithinBrake || pos == BelowBrake)
    {
        return true;
    }
    return false;
}

int FurthestFloorWithOppLight(Direction dir)
{
    bool up = IsUp(dir);
    int start = up ? NumFloors : 1;
    int inc = up ? -1 : 1;

    int furthest = NoFloorAvailable;
    for (int floor = start; floor >= 1 && floor <= NumFloors; floor += inc)
    {
        ReletivePosition pos = WhereIs(floor);
        if (GetCallLight(floor, !up) && (pos == Equal || (up && IsAbove(pos)) || (!up && IsBelow(pos))))
        {
            furthest = floor;
            break;
        }

        if (GetCallLight(floor, up))
            break;
    }

    return furthest;
}

void StateIdle(Elevator *elevator)
{
    elevator->nextFloor = WhatFloorToGoTo(elevator->direction);
    if (elevator->nextFloor == NoFloorAvailable)
    {
        return;
    }

    elevator->state = Moving;
    SetBrake(false);
    switch (WhereIs(elevator->nextFloor))
    {
    case AboveBrake:
    case AboveWithinBrake:
        elevator->direction = GoingUp;
        break;
    case BelowBrake:
    case BelowWithinBrake:
        elevator->state = Moving;
        elevator->direction = GoingDown;
        break;
    }
}

void StateMoving(Elevator *elevator)
{
    elevator->nextFloor = WhatFloorToGoToInThisDirection(IsUp(elevator->direction));
    ReletivePosition relativePos = WhereIs(elevator->nextFloor);

    if (relativePos == Equal)
    {
        SetMotorPower(0);
        SetBrake(true);
        SetDoor(elevator->nextFloor, true);

        SetPanelFloorLight(elevator->nextFloor, false);

        bool up = IsUp(elevator->direction);
        SetCallLight(elevator->nextFloor, up, false);
        if (elevator->nextFloor == FurthestFloorWithOppLight(elevator->direction))
        {
            SetCallLight(elevator->nextFloor, !up, false);
            elevator->direction = ReverseDirection(elevator->direction);
        }

        elevator->state = OpenDoor;
    }
    else
    {
        MoveTo(elevator->nextFloor, relativePos, elevator->controller);
    }
}

void StateOpenDoor(Elevator *elevator)
{
    if (IsDoorOpen(elevator->nextFloor))
    {
        elevator->state = ClosingDoor;
        ResetTimer();
    }
}

void StateClosingDoor(Elevator *elevator)
{
    if (GetTimer() > DoorOpenTime)
    {
        SetDoor(elevator->nextFloor, false);
    }

    if (IsDoorClosed(elevator->nextFloor))
    {
        elevator->state = Idle;
    }
}