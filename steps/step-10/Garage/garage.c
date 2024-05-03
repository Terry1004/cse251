#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "GarageLib.h"

typedef enum
{
    DoorClosed,
    DoorOpening,
    DoorOpen,
    DoorClosing,
} DoorState;

void StateDoorClosed(DoorState *state);
void StateDoorOpening(DoorState *state);
void StateDoorOpen(DoorState *state);
void StateDoorClosing(DoorState *state);

int main()
{
    DoorState state = DoorClosed;

    printf("Garage Startup\n");
    GarageStartup();

    while (IsGarageRunning())
    {
        switch (state)
        {
        case DoorClosed:
            StateDoorClosed(&state);
            break;
        case DoorOpening:
            StateDoorOpening(&state);
            break;
        case DoorOpen:
            StateDoorOpen(&state);
            break;
        case DoorClosing:
            StateDoorClosing(&state);
            break;
        }

    }

    printf("Garage Shutdown\n");
    GarageShutdown();
    return 0;
}

void StateDoorClosed(DoorState *state)
{
    if (WasButtonPressed())
    {
        SetMotorPower(1);
        *state = DoorOpening;
    }
}

void StateDoorOpening(DoorState *state)
{
    if (GetDoorPosition() >= (DoorHeight - DoorTolerance))
    {
        SetMotorPower(0);
        *state = DoorOpen;
        ResetTimer();
    }
    else if (IsBeamBroken())
    {
        WasButtonPressed(); // ignore button
        return;
    }
    else if(WasButtonPressed())
    {
        SetMotorPower(-1);
        *state = DoorClosing;
    }
}

void StateDoorOpen(DoorState *state)
{
    if (IsBeamBroken())
    {
        WasButtonPressed(); // ignore button
        ResetTimer();
        return;
    }

    if(WasButtonPressed() || GetTimer() > 10)
    {
        SetMotorPower(-1);
        *state = DoorClosing;
    }
}

void StateDoorClosing(DoorState *state)
{
    if(GetDoorPosition() < DoorTolerance)
    {
        SetMotorPower(0);
        *state = DoorClosed;
    }
    else if(WasButtonPressed() || IsBeamBroken())
    {
        SetMotorPower(1);
        *state = DoorOpening;
    }
}