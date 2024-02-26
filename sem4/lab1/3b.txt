#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <thread>

#define QUEUE_SIZE 100

using namespace std;
using namespace chrono;
using namespace this_thread;

struct QueueNode {
    char* data;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
    int size;
};

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void QPUSH(struct Queue* queue, const char* value) {
    if (queue->size >= QUEUE_SIZE) {
        printf("Queue is full. Cannot enqueue more elements.\n");
        return;
    }

    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = _strdup(value); // strdup выделяет память для копии строки
    newNode->next = NULL;

    if (queue->size == 0) {
        queue->front = newNode;
    }
    else {
        queue->rear->next = newNode;
    }

    queue->rear = newNode;
    queue->size++;
}

void QPOP(struct Queue* queue, char** value) {
    if (queue->size == 0) {
        printf("Queue is empty. Cannot dequeue.\n");
        *value = NULL;
        return;
    }

    struct QueueNode* frontNode = queue->front;
    *value = frontNode->data;
    queue->front = frontNode->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(frontNode);
    queue->size--;
}

void fibonacci() {
    int n = 10; 
    int a = 0, b = 1, c, i;

    printf("Fibonacci to %d:\n", n);
    printf("%d, %d, ", a, b);

    for (i = 2; i < n; i++) {
        c = a + b;
        printf("%d, ", c);
        a = b;
        b = c;
    }

    printf("\n");
}

void sumArray() {
    int array[] = { 1, 2, 3, 4, 5 };
    int sum = 0;

    printf("Array: ");
    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        printf("%d ", array[i]);
        sum += array[i];
    }

    printf("\nSum: %d\n", sum);
}

void processRequests(struct Queue* queue) {
    char* request;
    while (queue->size > 0) {
        QPOP(queue, &request);

        sleep_for(seconds(1));

        printf("Processing: %s\n", request);

        if (strcmp(request, "Request 1") == 0) {
            sumArray();
        }

        else if (strcmp(request, "Request 2") == 0) {
            fibonacci();
        }

        else if (strcmp(request, "Request 3") == 0) {
            printf("Hello world!");
        }

        free(request);
    }
}

int main() {
    struct Queue* requestQueue = createQueue();

    QPUSH(requestQueue, "Request 1");
    QPUSH(requestQueue, "Request 2");
    QPUSH(requestQueue, "Request 3");

    processRequests(requestQueue);

    free(requestQueue);

    return 0;
}