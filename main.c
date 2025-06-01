/**
 * ACE6123 Algorithms and Data Structures
 * Trimester March 2025
 * Take-Home Group Assignment (30%)
 * 
 * --------------------------------------
 * 
 * Dynamic Dataset: Table reservation system
 * 
 * Students 1
 * Name: Lee Chong Chun
 * Id: 242UA244BZ
 * Major: CE
 * 
 * Students 2
 * Name: Kiruban
 * Id: 
 * Major: CE
 * 
 * Students 3
 * Name: Maya Alysha Binti Mohd Imran
 * Id: 
 * Major: CE
 * 
 * Students 4
 * Name: Muhammad Nabil Hafiz Bin Salmardi
 * Id: 
 * Major: CE
 * 
 * Students 5
 * Name: Nur Adlina Humaira Binti Akmal
 * Id: 
 * Major: CE
 * 
 */

#include <stdio.h>
#include <string.h>
#include "file.h"
#include "stack.h"
#include "prompt.h"

void printTable(struct Table *);
void printMenu();

int subproc_errno = 0;
char subproc_stderr[256], subproc_stdout[256];

int main(){
    char what;
    struct Table *head = NULL;
    struct Table *curr = NULL;
    head = initTableNode(0, "\0", "\0", "\0", "\0");
    head->next = NULL;

    loadFromFile(head);

    do {
        printMenu();
        char buffer[256];

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            what = buffer[0];
            switch(what-'0') {
                case 1: { // Add reservation
                    int table;
                    char name[NAME_LEN], phone[PHONE_LEN], date[DATE_LEN], time[TIME_LEN];

                    printf("Please fill in reservation details:\n");

                    getTable(&table, 0);
                    getName(name, 0);
                    getPhone(phone, 0);
                    getDate(date, 0);
                    getTime(time, 0);

                    push(table, name, phone, date, time, head);
                    strcpy(subproc_stdout, "\033[0;32mReservation added successfully\033[0m\n");
                    break;
                } case 2: { // Cancel reservation
                    if (empty(head, curr)) {
                        subproc_errno = 1;
                        strcpy(subproc_stderr, "No reservations exist yet.");
                    } else {
                        printTable(head);
                        char *ret = pop(head);
                        if (ret == NULL) {
                            subproc_errno = 1;
                            strcpy(subproc_stderr, "No matching reservation found!");
                        } else {
                            subproc_errno = 0;
                            sprintf(subproc_stdout, "\033[0;32mReservation cancelled successfully for \033[0;36m%s\033[0m\n", ret);
                        }
                    }
                    break;
                } case 3: { // View reservations
                    printTable(head);
                    break;
                } case 4: { // Search reservation
                    int table;
                    char name[NAME_LEN], phone[PHONE_LEN], date[DATE_LEN], time[TIME_LEN];

                    getTable(&table, 1);
                    getName(name, 1);
                    getPhone(phone, 1);
                    getDate(date, 1);
                    getTime(time, 1);

                    query(head, table, name, phone, date, time);
                    break;
                } default: {
                    subproc_errno = 1;
                    strcpy(subproc_stderr, "Invalid choice! Please try again: ");
                    break;
                }
            }
        }
    } while(what-'0');

    // save to stack to file on exit
    saveToFile(head);
    printf("Saving revervation information into dataset.txt...\n");

    return 0;
}

/**
 * Print operations
 * printTable(); - Prints the current reservations in a formatted table.
 * printMenu(); - Displays the main menu options.
 */
void printTable(struct Table *head) {
    struct Table *temp = head->next;
    if (temp == NULL) {
        subproc_errno = 1;
        strcpy(subproc_stderr, "No reservations exist yet.");
        return;
    }

    printf("\e[1;1H\e[2J");
    printf("\033[0;34mCurrent Reservations:\033[0m\n");
    printf("Table\tName                Phone               Date           Time\n");
    printf("-------------------------------------------------------------------\n");
    while (temp != NULL) {
        printf("%d\t%-20s%-20s%-15s%-5s\n", 
               temp->table, 
               temp->name, 
               temp->phone, 
               temp->date, 
               temp->time);
        temp = temp->next;
    }
    printf("-------------------------------------------------------------------\n");
    printf("Press Enter to continue...");
    (void)getchar();
}

void printMenu() {
    printf("\e[1;1H\e[2J");
    printf("Welcome to table revervatrion service, please enter your option:\n");
    printf("  \033[34m[1]\033[0m Make table reservation\n");
    printf("  \033[34m[2]\033[0m Cancel table reservation\n");
    printf("  \033[34m[3]\033[0m View all reservations\n");
    printf("  \033[34m[4]\033[0m Search reservation\n");
    printf("  \033[34m[0]\033[0m Exit\n");
    if (subproc_errno != 0) {
        fprintf(stderr, "\033[0;31m%s\033[0m\n", subproc_stderr);
    } else {
        printf("%s", subproc_stdout);
        subproc_stdout[0] = '\0';
    }
    printf("Enter your choice: ");
    subproc_errno = 0;
}
