#ifndef TYPES_H
#define TYPES_H

#define __USE_XOPEN
#include <time.h>

#define NAME_SIZE 51

typedef enum
{
    opt_insert = 1,
    opt_display = 2,
    opt_now = 3,
    opt_expire = 4,
    opt_exit = 0,
    opt_invalid = -1,
} MenuOption;

typedef struct
{
    char name[NAME_SIZE];
    time_t date;
    time_t start;
    time_t end;
} Event;

typedef struct
{
    Event *events;
    int num_events;
    int cap;
} Scheduler;

#endif