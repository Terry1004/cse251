#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "io.h"

MenuOption input_option()
{
    char buffer[BUFFER_SIZE];
    MenuOption opt;
    bool valid = false;

    printf("%d - Insert a new event\n", opt_insert);
    printf("%d - Display all events\n", opt_display);
    printf("%d - Now?\n", opt_now);
    printf("%d - Delete expired\n", opt_expire);
    printf("%d - Exit\n", opt_exit);

    do
    {
        printf("Please select an option: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        int len = strlen(buffer);
        if (len > 0)
        {
            buffer[len - 1] = '\0';
        }

        int opt_number = opt_invalid;
        sscanf(buffer, "%d", &opt_number);

        if (
            opt_number == opt_insert ||
            opt_number == opt_display ||
            opt_number == opt_now ||
            opt_number == opt_expire ||
            opt_number == opt_exit)
        {
            opt = opt_number;
            valid = true;
        }
    } while (!valid);

    return opt;
}

Event input_event()
{
    Event event;

    input_name(event.name, "What is the event: ");
    event.date = input_date("Event date: ");
    event.start = input_time("Start time: ", event.date);
    event.end = input_time("End time: ", event.date);

    return event;
}

void input_name(char *name, char *prompt)
{
    printf("%s", prompt);
    char buffer[BUFFER_SIZE];

    fgets(buffer, BUFFER_SIZE, stdin);
    while (buffer[0] == '\n')
        fgets(buffer, BUFFER_SIZE, stdin);

    int len = strlen(buffer);
    if (len > 0)
        buffer[len - 1] = '\0';

    strncpy(name, buffer, NAME_SIZE);
    name[NAME_SIZE - 1] = '\0';
}

time_t input_date(char *prompt)
{
    char buffer[BUFFER_SIZE];
    char *result;
    struct tm date = {0};

    do
    {
        printf("%s", prompt);

        fgets(buffer, BUFFER_SIZE, stdin);
        int len = strlen(buffer);
        if (len > 0)
            buffer[len - 1] = '\0';

        result = strptime(buffer, "%m/%d/%Y", &date);
    } while (result == NULL);

    return mktime(&date);
}

time_t input_time(char *prompt, time_t date)
{
    char buffer[100];
    char *result;

    struct tm time = *localtime(&date);

    do
    {
        printf("%s", prompt);

        fgets(buffer, sizeof(buffer), stdin);
        int len = strlen(buffer);
        if (len > 0)
            buffer[len - 1] = '\0';

        result = strptime(buffer, "%I:%M%p", &time);
    } while (result == NULL);

    return mktime(&time);
}

void format_time(struct tm data_tm, char buffer[])
{
    int hour = (data_tm.tm_hour + 11) % 12 + 1;
    int min = data_tm.tm_min;
    char *suffix = data_tm.tm_hour >= 12 ? "PM" : "AM";

    snprintf(buffer, TIME_STRING_SIZE, "%2d:%02d%s", hour, min, suffix);
}

void print_event(Event event)
{
    struct tm date = *localtime(&event.date);
    struct tm start_tm = *localtime(&event.start);
    struct tm end_tm = *localtime(&event.end);

    char start_time_str[TIME_STRING_SIZE], end_time_str[TIME_STRING_SIZE];
    format_time(start_tm, start_time_str);
    format_time(end_tm, end_time_str);
    printf(
        "%2d/%02d/%4d %s %s %s\n",
        date.tm_mon + 1,
        date.tm_mday,
        date.tm_year + 1900,
        start_time_str,
        end_time_str,
        event.name);
}
