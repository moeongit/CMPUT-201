#include "ex11q1.h"

// ############################################################################
// Vector
// ############################################################################

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

LinkedListNode* list_node_create(int item) {
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    if (node == NULL) {
        return NULL;
    }
    node->item = item;

    node->next = NULL;

    return node;
}

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
        return; 
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
        DoublyLinkedListNode* current;
        int i;

        if (at < l->length / 2) {
            current = l->start;
            i = 0;
            while (i < at) {
                current = current->next;
                i++;
            }
        } else {
            current = l->end;
            i = l->length - 1;
            while (i > at) {
                current = current->prev;
                i--;
            }
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

// ############################################################################
// Main
// ############################################################################
int main(void) {
    char line[1000];
    // Uncomment each for loop as you implement that part

    clock_t begin_vec = clock();
    Vec* v = vec_create();

    for (int i = 0; i < 100000; i++) {
       int a, b;
       if (getchar() == 'i') {
           scanf("%s %d %s %d\n", line, &a, line, &b);
           vec_insert_at(v, b, a);
       } else {
           scanf("%s\n", line);
           vec_print(v);
       }
    }

    vec_free(v);
    clock_t end_vec = clock();

    clock_t begin_list = clock();
    LinkedList* l = list_create();

    for (int i = 0; i < 100000; i++) {
       int a, b;
       if (getchar() == 'i') {
           scanf("%s %d %s %d\n", line, &a, line, &b);
           list_insert_at(l, b, a);
       } else {
           scanf("%s\n", line);
           list_print(l);
       }
    }

    list_free(l);
    clock_t end_list = clock();

    clock_t begin_dlist = clock();
    DoublyLinkedList* dlist = dlist_create();

    for (int i = 0; i < 100000; i++) {
       int a, b;
       if (getchar() == 'i') {
           scanf("%s %d %s %d\n", line, &a, line, &b);
           dlist_insert_at(dlist, b, a);
       } else {
           scanf("%s\n", line);
           dlist_print(dlist);
       }
    }

    dlist_free(dlist);
    clock_t end_dlist = clock();

    fprintf(stderr, "Vector: %gs\n", (double)(end_vec - begin_vec) / CLOCKS_PER_SEC);
    fprintf(stderr, "Linked List: %gs\n", (double)(end_list - begin_list) / CLOCKS_PER_SEC);
    fprintf(stderr, "Doubly Linked List: %gs\n", (double)(end_dlist - begin_dlist) / CLOCKS_PER_SEC);
}
