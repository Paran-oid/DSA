#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void print_queue(Queue* queue)
{
    ListNode* node = queue->head;
    printf("Queue (front -> rear): ");
    while (node) {
        printf("%d -> ", *(int*)node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main()
{
    Queue queue;
    queue_create(&queue, NULL, free); // Use free to destroy data when dequeuing

    // Enqueue values
    for (int i = 1; i <= 5; i++) {
        int* value = malloc(sizeof(int));
        *value = i;
        queue_enqueue(&queue, value);
    }

    printf("After enqueueing 5 values:\n");
    print_queue(&queue);

    // Peek at the front value
    int* front_value = (int*)queue_peek(&queue);
    if (front_value) {
        printf("Front of queue: %d\n", *front_value);
    }

    // Dequeue values one by one
    for (int i = 0; i < 3; i++) {
        int* dequeued_value;
        if (queue_dequeue(&queue, (void**)&dequeued_value) == 0) {
            printf("Dequeued: %d\n", *dequeued_value);
            free(dequeued_value);
        } else {
            printf("Queue is empty!\n");
        }
        print_queue(&queue);
    }

    // Destroy queue
    queue_destroy(&queue);
    printf("Queue destroyed.\n");

    return 0;
}
