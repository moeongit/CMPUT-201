#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* head;   
    int length;    
    int capacity;  
    int front;     
    int rear;      
} Ring;

void initializeRing(Ring *ring, int capacity);
void resizeRing(Ring *ring);
void insertFront(Ring *ring, int value);
void insertBack(Ring *ring, int value);
int removeFront(Ring *ring);
int removeBack(Ring *ring);
void cleanupRing(Ring *ring);

int main() {
    const int initialCapacity = 10;
    Ring frontHalf, backHalf;
    initializeRing(&frontHalf, initialCapacity);
    initializeRing(&backHalf, initialCapacity);

    char command;
    int x, student_id;

    while (scanf(" %c", &command) != EOF) {
        int totalLength = frontHalf.length + backHalf.length;

        switch (command) {
            case 'N':
            case 'C':
                scanf("%d %d", &x, &student_id);
                int skipPosition = (command == 'C') ? (totalLength + 1) / 2 : totalLength;

                if (skipPosition < x) {
                    if (command == 'C') {
                        if (totalLength % 2 == 0) {
                            insertBack(&frontHalf, student_id);
                        } else {
                            insertFront(&backHalf, student_id);
                        }
                    } else {
                        insertBack(&backHalf, student_id);
                    }
                }
                break;
            case 'F':
                if (frontHalf.length > 0) {
                    printf("%d\n", removeFront(&frontHalf));
                } else if (backHalf.length > 0) {
                    printf("%d\n", removeBack(&backHalf));
                } else {
                    printf("empty\n");
                }
                break;
            case 'L':
                if (backHalf.length > 0) {
                    removeBack(&backHalf);
                } else if (frontHalf.length > 0) {
                    removeFront(&frontHalf);
                }
                break;
        }

        while (frontHalf.length > backHalf.length + 1) {
            insertFront(&backHalf, removeBack(&frontHalf));
        }
        while (backHalf.length > frontHalf.length) {
            insertBack(&frontHalf, removeFront(&backHalf));
        }
    }

    cleanupRing(&frontHalf);
    cleanupRing(&backHalf);

    return 0;
}

void initializeRing(Ring *ring, int capacity) {
    ring->head = (int*) malloc(capacity * sizeof(int));
    if (ring->head == NULL) {
        fprintf(stderr, "Failed to allocate memory for ring head\n");
        exit(EXIT_FAILURE);
    }
    ring->length = 0;
    ring->capacity = capacity;
    ring->front = 0;
    ring->rear = -1;
}

void resizeRing(Ring *ring) {
    int newCapacity = ring->capacity * 2;
    int* newhead = (int*) realloc(ring->head, newCapacity * sizeof(int));
    if (newhead == NULL) {
        fprintf(stderr, "Failed to reallocate memory for ring head\n");
        exit(EXIT_FAILURE);
    }
    ring->head = newhead;
    ring->capacity = newCapacity;
}

void insertFront(Ring *ring, int value) {
    if (ring->length == ring->capacity) {
        resizeRing(ring);
    }
    ring->front = (ring->front - 1 + ring->capacity) % ring->capacity;
    ring->head[ring->front] = value;
    ring->length++;
}

void insertBack(Ring *ring, int value) {
    if (ring->length == ring->capacity) {
        resizeRing(ring);
    }
    ring->rear = (ring->rear + 1) % ring->capacity;
    ring->head[ring->rear] = value;
    ring->length++;
}

int removeFront(Ring *ring) {
    if (ring->length == 0) {
        fprintf(stderr, "Attempted to remove from an empty ring head\n");
        exit(EXIT_FAILURE);
    }
    int value = ring->head[ring->front];
    ring->front = (ring->front + 1) % ring->capacity;
    ring->length--;
    return value;
}

int removeBack(Ring *ring) {
    if (ring->length == 0) {
        fprintf(stderr, "Attempted to remove from an empty ring head\n");
        exit(EXIT_FAILURE);
    }
    int value = ring->head[ring->rear];
    ring->rear = (ring->rear - 1 + ring->capacity) % ring->capacity;
    ring->length--;
    return value;
}

void cleanupRing(Ring *ring) {
    free(ring->head);
    ring->head = NULL;
    ring->length = 0;
    ring->capacity = 0;
    ring->front = 0;
    ring->rear = -1;
}
