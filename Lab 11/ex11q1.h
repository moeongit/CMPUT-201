#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// ############################################################################
// Vector
// ############################################################################
typedef struct {
    int length;
    int capacity;
    int* storage;
} Vec;

Vec* vec_create(void) {
    Vec* vec = malloc(sizeof(Vec));
    if (!vec) {
        return NULL; 
    }

    vec->capacity = 10;
    vec->length = 0;
    vec->storage = malloc(sizeof(int) * vec->capacity);

    if (!vec->storage) {
        free(vec);
        return NULL;
    }

    return vec;
}

void vec_insert_at(Vec* vec, int at, int item) {
    if (vec == NULL || at > vec->length || at < 0) {
        return; 
    }

    if (vec->length == vec->capacity) {
        int NewCapacity = vec->capacity * 2;
        int* NewStorage = realloc(vec->storage, sizeof(int) * NewCapacity);
        if (!NewStorage) {
            return; 
        }
        vec->storage = NewStorage;
        vec->capacity = NewCapacity;
    }

    for (int i = vec->length; i > at; --i) {
        vec->storage[i] = vec->storage[i - 1];
    }

    vec->storage[at] = item;
    vec->length++;
}

void vec_print(Vec* vec) {
    if (vec == NULL || vec->length == 0) {
        printf("[]\n");
        return;
    }

    printf("[");
    for (int i = 0; i < vec->length; ++i) {
        printf("%d", vec->storage[i]);
        if (i < vec->length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void vec_free(Vec* vec) {
    if (vec) {
        free(vec->storage);
        free(vec);
    }
}


// ############################################################################
// Linked List
// ############################################################################
typedef struct LinkedListNode {
    int item;
    struct LinkedListNode* next;
} LinkedListNode;

LinkedListNode* list_node_create(int item) {
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    if (node == NULL) {
        return NULL;
    }
    node->item = item;
    node->next = NULL;
    return node;
}

typedef struct {
    int length;
    LinkedListNode* start;
} LinkedList;

LinkedList* list_create(void) {
    LinkedList* list = malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->length = 0;
    list->start = NULL;
    return list;
}

void list_insert_at(LinkedList* list, int at, int item) {
    if (list == NULL || at < 0 || at > list->length) {
        return;
    }

    LinkedListNode* newNode = list_node_create(item);
    if (newNode == NULL) {
        return; 
    }

    if (at == 0) {
        newNode->next = list->start;
        list->start = newNode;
    } else {
        LinkedListNode* current = list->start;
        for (int i = 0; i < at - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    list->length++;
}

void list_print(LinkedList* list) {
    if (list == NULL || list->start == NULL) {
        printf("[]\n");
        return;
    }

    printf("[");
    LinkedListNode* current = list->start;
    while (current != NULL) {
        printf("%d", current->item);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

void list_free(LinkedList* list) {
    if (list == NULL) {
        return;
    }

    LinkedListNode* current = list->start;
    while (current != NULL) {
        LinkedListNode* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}


// ############################################################################
// Doubly Linked List
// ############################################################################
typedef struct DoublyLinkedListNode {
    int item;
    struct DoublyLinkedListNode* prev;
    struct DoublyLinkedListNode* next;
} DoublyLinkedListNode;

DoublyLinkedListNode* dlist_node_create(int item) {
    DoublyLinkedListNode* node = malloc(sizeof(DoublyLinkedListNode));
    if (node == NULL) {
        return NULL;
    }
    node->item = item;
    node->prev = NULL;
    node->next = NULL;
    return node;
}


typedef struct {
    int length;
    DoublyLinkedListNode* start;
    DoublyLinkedListNode* end;
} DoublyLinkedList;

DoublyLinkedList* dlist_create(void) {
    DoublyLinkedList* list = malloc(sizeof(DoublyLinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->length = 0;
    list->start = NULL;
    list->end = NULL;
    return list;
}

void dlist_insert_at(DoublyLinkedList* l, int at, int item) {
    if (l == NULL || at < 0 || at > l->length) {
        return; // Invalid input
    }

    DoublyLinkedListNode* newNode = dlist_node_create(item);
    if (newNode == NULL) {
        return;
    }

    if (l->length == 0) {
        l->start = newNode;
        l->end = newNode;
    } else if (at == 0) {
        newNode->next = l->start;
        l->start->prev = newNode;
        l->start = newNode;
    } else if (at == l->length) {
        newNode->prev = l->end;
        l->end->next = newNode;
        l->end = newNode;
    } else {
        DoublyLinkedListNode* current = (at < l->length / 2) ? l->start : l->end;
        for (int i = (at < l->length / 2) ? 0 : l->length - 1; 
             (at < l->length / 2) ? i < at : i > at; 
             (at < l->length / 2) ? i++ : i--) {
            current = (at < l->length / 2) ? current->next : current->prev;
        }

        newNode->next = current;
        newNode->prev = current->prev;
        if (current->prev != NULL) {
            current->prev->next = newNode;
        }
        current->prev = newNode;
    }

    l->length++;
}


void dlist_print(DoublyLinkedList* l) {
    if (l == NULL || l->start == NULL) {
        printf("[]\n");
        return;
    }

    printf("[");
    DoublyLinkedListNode* current = l->start;
    while (current != NULL) {
        printf("%d", current->item);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

void dlist_free(DoublyLinkedList* l) {
    if (l == NULL) {
        return;
    }

    DoublyLinkedListNode* current = l->start;
    while (current != NULL) {
        DoublyLinkedListNode* next = current->next;
        free(current);
        current = next;
    }

    free(l);
}