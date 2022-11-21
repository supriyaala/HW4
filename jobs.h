#ifndef JOBS_H
#define JOBS_H

#include "queue.h"
#include <time.h>

typedef enum
{
    RUNNING,
    COMPLETED,
    WAITING
} status_t;

typedef struct
{
    int job_id;
    char *command;
    time_t start_time;
    time_t end_time;
    status_t status;
    int burst_time;

} jobs_t;

jobs_t *create_new_job(int job_id, char *command, int burst_time, status_t status);
void print_status(void *job);
void print_history(void *job);
void process_queue(queue *running, queue *ready, queue *history);

#endif