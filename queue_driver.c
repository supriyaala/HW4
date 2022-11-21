/* Driver program to which is testing the queue implementation */
/* Use the Makefile provided or compile using: gcc -Wall queue.c qdriver.c */

#include <stdio.h>
#include "queue.h"
#include "jobs.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <no_of_jobs>", argv[0]);
		return 1;
	}
	queue *jobs_ready = queue_init(100);
	queue *jobs_running = queue_init(atoi(argv[1]));
	queue *jobs_history = queue_init(100);
	char command[100];
	char job_name[100];
	int time_ = 0;
	int job_id = 1;
	while (1)
	{
		printf("Enter command> ");
		fgets(command, 100, stdin);
		if (strncmp(command, "submithistory", (size_t)13) == 0)
		{
			printf("Job ID\tCommand\t\t\t\t\tStart Time\t\tEnd Time\t\t\tStatus\n");
			queue_display(jobs_history, print_history);
		}
		else if (strncmp(command, "submit", (size_t)6) == 0)
		{
			sscanf(command, "submit %s %d", job_name, &time_);
			jobs_t *new_job;
			if (jobs_running->size == jobs_running->count)
			{
				new_job = create_new_job(job_id, job_name, time_ / 1000 + 5, WAITING);
				queue_insert(jobs_ready, new_job);									   
			}
			else
			{
				new_job = create_new_job(job_id, job_name, time_ / 1000 + 5, RUNNING);
				queue_insert(jobs_running, new_job);
			}

			printf("job %d added to queue\n", job_id++);
		}
		else if (strncmp(command, "showjobs", (size_t)8) == 0)
		{
			if (jobs_ready->count || jobs_running->count)
			{
				printf("Job ID\tCommand\t\t\tStatus\n");
				queue_display(jobs_running, print_status);
				queue_display(jobs_ready, print_status);
			}
		}

		else if (strncmp(command, "quit", (size_t)4) == 0)
		{
			break;
		}
		else
		{
			printf("Invalid command. Please try again.\n");
		}

		process_queue(jobs_running, jobs_ready, jobs_history);
	}

	queue_destroy(jobs_ready);
	queue_destroy(jobs_running);
	queue_destroy(jobs_history);

	return 0;
}
