#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "scheduler.h"

int main()
{
    MenuOption opt;
    Scheduler scheduler = new_scheduler(INIT_SCHEDULER_CAP);
    bool end_loop = false;

    do
    {
        opt = input_option();
        switch (opt)
        {
        case opt_insert:
        {
            Event event = input_event();
            if (!insert_event(&scheduler, event))
            {
                end_loop = true;
            }
            to_file(&scheduler);
            break;
        }
        case opt_display:
            for (int i = 0; i < scheduler.num_events; i++)
            {
                print_event(scheduler.events[i]);
            }
            break;
        case opt_now:
        {
            show_now(&scheduler);
            break;
        }
        case opt_expire:
            expire_event(&scheduler);
            to_file(&scheduler);
            break;
        case opt_exit:
        case opt_invalid:
            end_loop = true;
            break;
        }
    } while (!end_loop);
}

Scheduler new_scheduler(int cap)
{
    Event *events = malloc(sizeof(Event) * cap);
    Scheduler scheduler = {events, 0, cap};
    from_file(&scheduler);
    return scheduler;
}

bool insert_event(Scheduler *scheduler, Event event)
{
    scheduler->num_events += 1;
    if (scheduler->num_events > scheduler->cap)
    {
        scheduler->cap *= 2;
        scheduler->events = realloc(scheduler->events, sizeof(Event) * scheduler->cap);
        if (scheduler->events == NULL)
        {
            printf("Out of memory\n");
            return false;
        }
    }

    int dest = scheduler->num_events - 1;
    bool inserted = false;
    bool overlapped = false;
    for (int src = scheduler->num_events - 2; src >= 0; src--)
    {
        Event curr_event = scheduler->events[src];
        if (
            (curr_event.start >= event.start && curr_event.start < event.end) ||
            (event.start >= curr_event.start && event.start < curr_event.end))
        {
            if (!overlapped)
            {
                overlapped = true;
                printf("Warning, this event overlaps: \n");
            }
            print_event(curr_event);
        }

        if (!inserted && curr_event.start <= event.start)
        {
            inserted = true;
            scheduler->events[dest--] = event;
        }
        scheduler->events[dest--] = curr_event;
    }

    if (!inserted)
    {
        scheduler->events[0] = event;
    }

    return true;
}

void show_now(Scheduler *scheduler)
{
    time_t now = time(NULL);
    bool active = false;
    for (int i = 0; i < scheduler->num_events; i++)
    {
        if (now >= scheduler->events[i].start && now <= scheduler->events[i].end)
        {
            if (!active)
            {
                active = true;
                printf("Currently active events: \n");
            }
            print_event(scheduler->events[i]);
        }
    }
}

void expire_event(Scheduler *scheduler)
{
    time_t now = time(NULL);
    int dest = 0;

    int num_deleted = 0;
    for (int src = 0; src < scheduler->num_events; src++)
    {
        Event current_event = scheduler->events[src];
        if (current_event.end >= now)
        {
            scheduler->events[dest++] = current_event;
        }
        else
        {
            if (num_deleted == 0)
            {
                printf("Deleting:\n");
            }
            print_event(current_event);
            num_deleted++;
        }
    }
    scheduler->num_events -= num_deleted;

    if (num_deleted == 0)
    {
        printf("No expired events\n");
    }
}