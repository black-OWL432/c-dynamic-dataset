/**
 * modified from stack.c: LL implementation for characters
 * (c) 2000 by J D White
 * Stack operations
 * struct Table* initTableNode(); - Initializes a new table node with the given parameters.
 * push(); - Pushes a new reservation onto the stack.
 * pop(); - Pops a reservation from the stack based on user input.
 * empty(); - Checks if the stack is empty.
 */

#include "stack.h"
#include "prompt.h"

struct Table* initTableNode(int table, char *name, char *phone, char *date, char *time) {
    struct Table *temp = (struct Table *)malloc(sizeof(struct Table));
    temp->table = table;
    strcpy(temp->name, name);
    strcpy(temp->phone, phone);
    strcpy(temp->date, date);
    strcpy(temp->time, time);

    temp->next = NULL;
    return temp;
}

void push(int table, char *name, char *phone, char *date, char *time, struct Table *head) {
    struct Table *temp;
    temp = initTableNode(table, name, phone, date, time);
    temp->next = head->next;
    head->next = temp;
}

char pop(struct Table *curr) {
    struct Table *temp;
    int targetTable;
    char targetDate[DATE_LEN], targetTime[TIME_LEN];
    
    getTable(&targetTable);
    getDate(targetDate);
    getTime(targetTime);

    struct Table *prev = curr;
    temp = curr->next;

    while (temp != NULL) {
        if (temp->table == targetTable && 
            strcmp(temp->date, targetDate) == 0 &&
            strcmp(temp->time, targetTime) == 0) {

            prev->next = temp->next;
            printf("Reservation cancelled for \033[0;34m%s\033[0m, press Enter to continue...\n", temp->name);
            free(temp);
            (void)getchar();
            return 1;
        }
        prev = temp;
        temp = temp->next;
    }

    fprintf(stderr, "\033[0;31mNo matching reservation found!\033[0m\n");
    return 0;
}

char empty(struct Table *head, struct Table *curr){
    return head->next == curr;
}
