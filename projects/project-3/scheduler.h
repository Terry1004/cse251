#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "types.h"
#include "io.h"

#define INIT_SCHEDULER_CAP 2

Scheduler new_scheduler(int cap);
bool insert_event(Scheduler *scheduler, Event event);
void show_now(Scheduler *scheduler);
void expire_event(Scheduler *scheduler);

#endif