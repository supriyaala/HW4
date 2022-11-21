#include "jobs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

jobs_t *create_new_job(int job_id, char *command, int burst_time, status_t status)
{
    jobs_t *new_job = (jobs_t *)malloc(sizeof(jobs_t));
    new_job->job_id = job_id;
    new_job->command = (char *)malloc(sizeof(char) * (strlen(command) + 1));
    strcpy(new_job->command, command);
    new_job->burst_time = burst_time;
    new_job->status = status;
    if (status == RUNNING)
    {
        new_job->start_time = time(NULL);
    }
    else
    {
        new_job->start_time = 0;
    }
    return new_job; // return the new job
}

void print_status(void *job)
{
    jobs_t *job_ptr = (jobs_t *)job;
    char status[20];
    switch (job_ptr->status)
    {
    case RUNNING:
        strcpy(status, "Running");
        break;
    case COMPLETED:
        strcpy(status, "Success");
        break;
    case WAITING:
        strcpy(status, "Waiting");
        break;
    }

    printf("%d\t%s\t%s\n", job_ptr->job_id, job_ptr->command, status);
}

void print_history(void *job)
{
    jobs_t *job_ptr = (jobs_t *)job;
    char status[20];
    switch (job_ptr->status)
    {
    case RUNNING:
        strcpy(status, "Running");
        break;
    case COMPLETED:
        strcpy(status, "Success");
        break;
    case WAITING:
        strcpy(status, "Waiting");
        break;
    }

    char *start_time = malloc(sizeof(char) * 100);
    char *end_time = malloc(sizeof(char) * 100);

    strftime(start_time, 100, "%a %b %d %H:%M:%S %Y", localtime(&job_ptr->start_time));
    strftime(end_time, 100, "%a %b %d %H:%M:%S %Y", localtime(&job_ptr->end_time));

    printf("%d\t%s\t%s\t%s\t%s\n", job_ptr->job_id, job_ptr->command, start_time, end_time, status);
}

void process_queue(queue *running, queue *ready, queue *history)
{
    jobs_t *job_ptr = (jobs_t *)running->buffer[running->start];
    if (job_ptr->start_time + job_ptr->burst_time <= time(NULL))
    {
        job_ptr->status = COMPLETED;
        job_ptr->end_time = time(NULL);

        queue_insert(history, queue_delete(running));
        if (ready->count > 0)
        {
            job_ptr = (jobs_t *)ready->buffer[ready->start];
            job_ptr->status = RUNNING;
            job_ptr->start_time = time(NULL);
            queue_insert(running, queue_delete(ready));
        }
    }

    if (running->count < running->size && ready->count > 0)
    {
        job_ptr = (jobs_t *)ready->buffer[ready->start];
        job_ptr->status = RUNNING;
        job_ptr->start_time = time(NULL);
        queue_insert(running, queue_delete(ready));
    }
}