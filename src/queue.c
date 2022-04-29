#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void moveUp(struct queue_t*);
void moveDown(struct queue_t*, int);
int empty(struct queue_t * q) {
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
	/* TODO: put a new process to queue [q] */
	if (q->size != MAX_QUEUE_SIZE)
	{
		q->proc[q->size++] = proc;
		moveUp(q);	
	}
	

	// if (q->size == MAX_QUEUE_SIZE) return ;
	// q->proc[q->size++] = proc;
}

struct pcb_t * dequeue(struct queue_t * q) {
		
	/* TODO: return a pcb whose prioprity is the highest
	 * in the queue [q] and remember to remove it from q
	 * */
	if (!empty(q))
	{
		
		struct pcb_t* rs = q->proc[0];
		q->proc[0] = q->proc[--q->size];
		q->proc[q->size] = NULL;
		moveDown(q, 0);
		return rs;
	}
	return NULL;

	// if(q->size!=0)
	// {
	// 	struct pcb_t* temp_proc=NULL;
	// 	int max_priority=0;
	// 	int max_idx=0;
	// 	int i;
	// 	for(i=0;i<q->size;++i)
	// 	{
	// 		if(q->proc[i]->priority>max_priority)
	// 		{
	// 			temp_proc=q->proc[i];
	// 			max_priority=temp_proc->priority;
	// 			max_idx=i;
	// 		}	
	// 	}
	// 	for(i=max_idx;i<q->size-1;++i)
	// 		q->proc[i]=q->proc[i+1];
	// 	q->proc[q->size-1]=NULL;
	// 	--q->size;
	// 	return temp_proc;
	// }
	// return NULL;
}


int parent(int i)
{
	return (i-1)/2;
}
int leftChild(int i)
{
	return ((2*i) + 1);
}
int rightChild(int i)
{
	return ((2*i) + 2);
}
void moveUp(struct queue_t *q)
{
	int i = q->size-1;
	struct pcb_t* tmp;
	
	while (i > 0 && q->proc[parent(i)]->priority < q->proc[i]->priority)
	{
		tmp = q->proc[parent(i)];
		q->proc[parent(i)] = q->proc[i];
		q->proc[i] = tmp;
		i = parent(i);
	}
	tmp = NULL;
}

void moveDown(struct queue_t *q, int idx)
{
	int minidx = idx;
	int l = leftChild(idx);
	if (l < q->size && q->proc[l]->priority > q->proc[minidx]->priority)
	{
		minidx = l;
	}

	int r = rightChild(idx);

	if (r < q->size && q->proc[r]->priority > q->proc[minidx]->priority)
	{
		minidx = r;
	}

	if (idx != minidx)
	{
		struct pcb_t* tmp = q->proc[idx];
		q->proc[idx] = q->proc[minidx];
		q->proc[minidx] = tmp;
		tmp = NULL;
		moveDown(q, minidx);
	}
}