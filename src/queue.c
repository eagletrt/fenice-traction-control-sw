#include "queue.h"


int emptyp(const queue_t * q) 
{ 
    int res = 0;
    res = (q->head == q->tail);
  return res;
}

void queue_init(queue_t * q) 
{
    q->tail = 0;
    q->head = 0;
}

void enqueue (queue_element_t e, queue_t * q) 
{ 
  q->data[q->tail] = e;
  q->tail = (q->tail + 1)%(DIM_queue); 
}

int queue_first(const queue_t * q, queue_element_t* element) 
{ 
  int res = 0;
  if (emptyp(q)) 
    res = 0;
  else {
    *element = q->data[q->head];
    res = 1; 
  }
  return res; 
}

void dequeue(queue_t * q) 
{ 
  if (!emptyp(q)) {
    q->head = (q->head + 1)/(DIM_queue);
  }
}
