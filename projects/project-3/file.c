#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

void from_file(Scheduler *scheduler)
{
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL)
    {
        printf("Couldn't open file=%s\n", FILE_NAME);
        return;
    }

    char buffer[BUFFER_SIZE];
    int num_events;
    fgets(buffer, sizeof(buffer), file);
    int len = strlen(buffer);
    if (len > 0)
        buffer[len - 1] = '\0';
    sscanf(buffer, "%d", &num_events);

    scheduler->num_events = num_events;
    if (num_events > scheduler->cap)
    {
        scheduler->cap = num_events;
        scheduler->events = realloc(scheduler->events, num_events * sizeof(Event));
    }

    for (int i = 0; i < num_events; i++)
    {
        scheduler->events[i] = input_event_from_file(file);
    }
    fclose(file);
}

Event input_event_from_file(FILE *file)
{
    Event event;
    input_name_from_file(event.name, file);
    event.start = input_time_from_file(file);
    event.end = input_time_from_file(file);
    event.date = extract_date(event.start);

    return event;
}

void input_name_from_file(char *name, FILE *file)
{
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, file);
    int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';

    strncpy(name, buffer, NAME_SIZE);
    name[NAME_SIZE - 1] = '\0';
}

time_t input_time_from_file(FILE *file)
{
    struct tm data_tm = {0};
    char buffer[BUFFER_SIZE];

    fgets(buffer, BUFFER_SIZE, file);
    int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';

    strptime(buffer, "%a %b %d %H:%M:%S %Y", &data_tm);
    return mktime(&data_tm);
}

time_t extract_date(time_t data_time)
{
    struct tm data_tm = *localtime(&data_time);
    data_tm.tm_min = 0;
    data_tm.tm_hour = 0;
    data_tm.tm_sec = 0;
    data_tm.tm_isdst = 0;

    return mktime(&data_tm);
}

void to_file(Scheduler *scheduler)
{
    FILE *file = fopen(FILE_NAME, "w");

    fprintf(file, "%d\n", scheduler->num_events);
    for (int i = 0; i < scheduler->num_events; i++)
    {
        fprintf(file, "%s\n", scheduler->events[i].name);
        fprintf(file, "%s", ctime(&scheduler->events[i].start));
        fprintf(file, "%s", ctime(&scheduler->events[i].end));
    }

    fclose(file);
}
