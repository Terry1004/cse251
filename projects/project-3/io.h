#ifndef IO_H
#define IO_H

#include "types.h"

#define BUFFER_SIZE 100
#define TIME_STRING_SIZE 8
#define FILE_NAME "schedule.dat"

MenuOption input_option();
Event input_event();

void input_name(char *name, char *prompt);
time_t input_date(char *prompt);
time_t input_time(char *prompt, time_t date);

void format_time(struct tm data_tm, char buffer[]);
void print_event(Event event);

void from_file(Scheduler* scheduler);
Event input_event_from_file(FILE *file);
void input_name_from_file(char *name, FILE *file);
time_t input_time_from_file(FILE *file);
time_t extract_date(time_t data_time);

void to_file(Scheduler* scheduler);

#endif
