/* Header file for the circular queue example */
#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct _queue
{
	int size;
	void **buffer;
	int start;
	int end;
	int count;
} queue;

queue *queue_init(int n);
int queue_insert(queue *q, void *item);
void *queue_delete(queue *q);
void queue_display(queue *q, void (*f)(void *));
void queue_destroy(queue *q);

#endif
