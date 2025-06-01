/**
 * modified from stack.c: LL implementation for characters
 * (c) 2000 by J D White
 * Stack operations
 * struct Table* initTableNode(); - Initializes a new table node with the given parameters.
 * push(); - Pushes a new reservation onto the stack.
 * pop(); - Pops a reservation from the stack based on user input.
 * empty(); - Checks if the stack is empty.
 * 
 * Custom stack related operations
 * isDuplicate(); - Checks if a reservation already exists in the stack.
 * query(); - Queries the stack for reservations based on user input.
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
    if (isDuplicate(head, table, date, time)) {
        fprintf(stderr, "\033[0;31mA reservation already exists!\033[0m\n");
        printf("Press enter to return...");
        (void)getchar();
        return;
    }

    struct Table *temp;
    temp = initTableNode(table, name, phone, date, time);
    temp->next = head->next;
    head->next = temp;
}

char * pop(struct Table *curr) {
    struct Table *temp;
    int targetTable;
    char *targetName = malloc(NAME_LEN);
    char targetDate[DATE_LEN], targetTime[TIME_LEN];
    
    getTable(&targetTable, 0);
    getDate(targetDate, 0);
    getTime(targetTime, 0);

    struct Table *prev = curr;
    temp = curr->next;

    while (temp != NULL) {
        if (temp->table == targetTable && 
            strcmp(temp->date, targetDate) == 0 &&
            strcmp(temp->time, targetTime) == 0) {

            prev->next = temp->next;
            strcpy(targetName, temp->name);
            free(temp);
            return targetName;
        }
        prev = temp;
        temp = temp->next;
    }

    free(targetName);
    return NULL;
}

char empty(struct Table *head, struct Table *curr){
    return head->next == curr;
}

int isDuplicate(struct Table *head, int table, char *date, char *time) {
    struct Table *temp = head->next;
    while (temp != NULL) {
        if (temp->table == table && strcmp(temp->date, date) == 0 && strcmp(temp->time, time) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void query(struct Table *head, int table, char *name, char *phone, char *date, char *time) {
    struct Table *temp = head->next;
    int found = 0;

    printf("\e[1;1H\e[2J");
    printf("\033[0;34mSearch Results:\033[0m\n");
    printf("Table\tName                Phone               Date           Time\n");
    printf("-------------------------------------------------------------------\n");

    while (temp != NULL) {
        if ((table == 0 || temp->table == table) &&
            (strlen(name) == 0 || strstr(temp->name, name) != NULL) &&
            (strlen(phone) == 0 || strstr(temp->phone, phone) != NULL) &&
            (strlen(date) == 0 || strstr(temp->date, date) != NULL) &&
            (strlen(time) == 0 || strstr(temp->time, time) != NULL)) {
            printf("%d\t%-20s%-20s%-15s%-5s\n", 
                   temp->table, 
                   temp->name, 
                   temp->phone, 
                   temp->date, 
                   temp->time);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("No matching reservations found.\n");
    }

    printf("-------------------------------------------------------------------\n");
    printf("Press Enter to return...");
    (void)getchar();
}
