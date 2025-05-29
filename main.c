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
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 20
#define PHONE_LEN 20
#define DATE_LEN 15
#define TIME_LEN 10

struct Table {
    int table;
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char date[DATE_LEN];
    char time[TIME_LEN];
    struct Table *next;
};

struct Table* initTableNode(int, char *, char *, char *, char *);
void push(int, char *, char *, char *, char *, struct Table *);
char pop(struct Table *);
char empty(struct Table *, struct Table *);
void printTable(struct Table *);
void printMenu();
void getTable(int *);
void getName(char *);
void getPhone(char *);
void getDate(char *);
void getTime(char *);

int main(){
    char what;
    struct Table *head = NULL;
    struct Table *curr = NULL;
    head = initTableNode(0, "\0", "\0", "\0", "\0");
    head->next = NULL;

    do {
        printMenu();
        char buffer[256];

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            what = buffer[0];
            switch(what-'0') {
                case 1:
                    int table;
                    char name[NAME_LEN], phone[PHONE_LEN], date[DATE_LEN], time[TIME_LEN];

                    printf("Please fill in reservation details:\n");

                    getTable(&table);
                    getName(name);
                    getPhone(phone);
                    getDate(date);
                    getTime(time);

                    push(table, name, phone, date, time, head);
                    printf("Reservation added successfully\n");
                    break;
                case 2:
                    if (empty(head, curr)) {
                        printf("No reservations exist\n");
                    } else {
                        printTable(head);
                        pop(head);
                    }
                    break;
                case 3:
                    printTable(head);
                    printf("Press Enter to continue...");
                    getchar();
                    break;
                default: break;
            }
        }
    } while(what-'0');
    printf("Exiting...\n");

    return 0;
}

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
            getchar();
            return 1;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("\033[0;31mNo matching reservation found!\033[0m\n");
    return 0;
}

char empty(struct Table *head, struct Table *curr){
    return head->next == curr;
}

void printTable(struct Table *head) {
    struct Table *temp = head->next;
    if (temp == NULL) {
        printf("\033[0;31mNo reservations exist.\033[0m\n");
        printf("Press Enter to continue...");
        getchar();
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
}

void printMenu() {
    printf("\e[1;1H\e[2J");
    printf("Welcome to table revervatrion service, please enter your option:\n");
    printf("  \033[34m[1]\033[0m Make table reservation\n");
    printf("  \033[34m[2]\033[0m Cancel table reservation\n");
    printf("  \033[34m[3]\033[0m View all reservations\n");
    printf("  \033[34m[0]\033[0m Exit\n");
    printf("Enter your choice: ");
}

void getTable(int *table) {
    char buffer[256];
    
    do {
        printf("Enter table number (1-50): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\033[0;31mInvalid input! Please enter a number between 1 and 50:\033[0m ");
            continue;
        }
        
        if (sscanf(buffer, "%d", table) != 1) {
            printf("\033[0;31mInvalid input! Please enter a number between 1 and 50:\033[0m ");
            continue;
        }

        if (*table <= 0 || *table > 50) {
            printf("\033[0;31mInvalid input! Please enter a number between 1 and 50:\033[0m ");
            continue;
        }
        break;
    } while (1);
}

void getName(char *name) {
    printf("Enter customer name: ");
    do {
        if (fgets(name, NAME_LEN, stdin) == NULL || name[0] == '\n') {
            printf("\033[0;31mInvalid input! Please enter a valid name:\033[0m ");
            continue;
        }
        name[strcspn(name, "\n")] = 0;
    } while (strlen(name) == 0);
}

void getPhone(char *phone) {
    do {
        printf("Enter phone number: ");
        if (fgets(phone, PHONE_LEN, stdin) == NULL || phone[0] == '\n') {
            printf("\033[0;31mInvalid input! Please enter a valid phone number: \033[0m");
            continue;
        }
        phone[strcspn(phone, "\n")] = 0;
    } while (strlen(phone) == 0);
}

void getDate(char *date) {
    int day, month, year;
    char buffer[256];

    printf("Enter reservation date (DD-MM-YYYY): ");
    do {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\033[0;31mInvalid date format! Use DD-MM-YYYY (e.g., 28-05-2025):\033[0m ");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) != 10 || buffer[2] != '-' || buffer[5] != '-') {
            printf("\033[0;31mInvalid date format! Use DD-MM-YYYY (e.g., 28-05-2025):\033[0m ");
            continue;
        }

        if (sscanf(buffer, "%d-%d-%d", &day, &month, &year) != 3 || 
            month < 1 || month > 12 || day < 1 || day > 31) {
            printf("\033[0;31mInvalid date format! Use DD-MM-YYYY (e.g., 28-05-2025):\033[0m ");
            continue;
        }

        strcpy(date, buffer);
        break;
    } while (1);
}

void getTime(char *time) {
    int hour;
    char meridiem[3];
    char buffer[256];

    printf("Enter reservation time (12HR format, e.g., 2pm): ");
    do {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\033[0;31mInvalid input! Please enter a valid time (e.g., 2pm):\033[0m ");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = 0;

        if (sscanf(buffer, "%d%2s", &hour, meridiem) != 2 || hour < 1 || hour > 12 ||
            (strcmp(meridiem, "am") != 0 && strcmp(meridiem, "pm") != 0)) {
            printf("\033[0;31mInvalid input! Please enter a valid time (e.g., 2pm):\033[0m ");
            continue;
        }

        strcpy(time, buffer);
        break;
    } while (1);
}
