/* Implementation of a simple circular queue using a static array */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* create the queue data structure and initialize it */
queue *queue_init(int n)
{
	queue *q = (queue *)malloc(sizeof(queue));
	q->size = n;
	q->buffer = malloc(sizeof(void *) * n);
	q->start = 0;
	q->end = 0;
	q->count = 0;

	return q;
}

/* insert an item into the queue, update the pointers and count, and
   return the no. of items in the queue (-1 if queue is null or full) */
int queue_insert(queue *q, void *item)
{
	if ((q == NULL) || (q->count == q->size) || (item == NULL))
		return -1;

	q->buffer[q->end % q->size] = item;
	q->end = (q->end + 1) % q->size;
	q->count++;
	return q->count;
}

/* delete an item from the queue, update the pointers and count, and
   return the item deleted (-1 if queue is null or empty) */
void *queue_delete(queue *q)
{
	if ((q == NULL) || (q->count == 0))
		return NULL;

	void *x = q->buffer[q->start];
	q->start = (q->start + 1) % q->size;
	q->count--;

	return x;
}

/* display the contents of the queue data structure */
void queue_display(queue *q, void (*f)(void *))
{
	int i;
	if (q != NULL && q->count != 0)
	{
		// printf("queue has %d elements, start = %d, end = %d\n",
		// 	   q->count, q->start, q->end);
		// printf("queue contents: ");
		for (i = 0; i < q->count; i++)
			f(q->buffer[(q->start + i) % q->size]);
	}
}

/* delete the queue data structure */
void queue_destroy(queue *q)
{
	for (int i = 0; i < q->count; i++)
		free(q->buffer[(q->start + i) % q->size]);
	free(q->buffer);
	free(q);
}
