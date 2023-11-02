#include "ex8q1.h"

typedef struct Entry {
    float index;
    int value;
    struct Entry* next;
} Entry;

Entry* insert_entry(Entry* head, float index, int value) {
    Entry* NewEntry = malloc(sizeof(Entry));
    NewEntry->index = index;
    NewEntry->value = value;
    NewEntry->next = NULL;
    
    if (!head) {
        return NewEntry;
    }

    if (head->index > index) {
        NewEntry->next = head;
        return NewEntry;
    }

    Entry* current = head;
    
    while (current->next && current->next->index < index) {
        current = current->next;
    }

    if (current->next && current->next->index == index) {
        current->next->value = value;
        free(NewEntry);
    } 
    else {
        NewEntry->next = current->next;
        current->next = NewEntry;
    }

    return head;
}

void print_array(Entry* head) {
    printf("[");
    Entry* current = head;
    while (current) {
        printf("%d", current->value);
        if (current->next){
            printf(", ");
        } 
        current = current->next;
    }
    printf("]\n");
}

void free_array(Entry* head) {
    while (head) {
        Entry* temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    int is_print, value;
    float index;
    Entry* ArrayHead = NULL;

    while (!feof(stdin)) {
        read_line(&is_print, &index, &value);
        if (is_print) {
            print_array(ArrayHead);
        } 
        else {
            ArrayHead = insert_entry(ArrayHead, index, value);
        }
    }

    free_array(ArrayHead);
    return 0;
}