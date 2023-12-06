#include <stdio.h>
#include <stdlib.h>

#define MaxStudents 3000000

int parent[MaxStudents + 1];

int Find(int student) {
    if (parent[student] != student) {
        parent[student] = Find(parent[student]);
    }
    return parent[student];
}

void UnionSets(int student1, int student2) {
    int parent1 = Find(student1);
    int parent2 = Find(student2);
    if (parent1 != parent2) {
        parent[parent1] = parent2;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }

    int n = atoi(argv[1]);

    for (int i = 1; i <= MaxStudents; i++) {
        parent[i] = i;
    }

    FILE *file = fopen(argv[3], "r");
    if (file == NULL) {
        return 1;
    }

    char command;
    int student1, student2;
    int result;

#ifdef FASTIO
    char *buff = malloc(10 * n);
    if (!buff) {
        fclose(file);
        return 1;
    }
    char *BuffPointer = buff;
#endif

    for (int i = 0; i < n; i++) {
        result = fscanf(file, " %c %d %d", &command, &student1, &student2);
        if (result != 3) {
            fclose(file);
#ifdef FASTIO
            free(buff);
#endif
            return 1;
        }

        if (command == 'j') {
            UnionSets(student1, student2);
        } 
        else if (command == '?') {
            if (Find(student1) == Find(student2)) {
#ifdef FASTIO
                BuffPointer += sprintf(BuffPointer, "T\n");
#else
                printf("T\n");
#endif
            } else {
#ifdef FASTIO
                BuffPointer += sprintf(BuffPointer, "F\n");
#else
                printf("F\n");
#endif
            }
        }
    }

#ifdef FASTIO
    printf("%s", buff);
    free(buff);
#endif
    fclose(file);
    return 0;
}