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
void loadFromFile(struct Table *);
void saveToFile(struct Table *);

int subproc_errno = 0;

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

                    getTable(&table);
                    getName(name);
                    getPhone(phone);
                    getDate(date);
                    getTime(time);

                    push(table, name, phone, date, time, head);
                    printf("Reservation added successfully\n");
                    subproc_errno = 0;
                    break;
                } case 2: { // Cancel reservation
                    if (empty(head, curr)) {
                        printf("No reservations exist\n");
                    } else {
                        printTable(head);
                        pop(head);
                    }
                    subproc_errno = 0;
                    break;
                } case 3: { // View reservations
                    printTable(head);
                    printf("Press Enter to continue...");
                    (void)getchar();
                    subproc_errno = 0;
                    break;
                } default: {
                    subproc_errno = 1;
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
 * Stack operations
 * struct Table* initTableNode(); - Initializes a new table node with the given parameters.
 * push(); - Pushes a new reservation onto the stack.
 * pop(); - Pops a reservation from the stack based on user input.
 * empty(); - Checks if the stack is empty.
 */
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

    printf("\033[0;31mNo matching reservation found!\033[0m\n");
    return 0;
}

char empty(struct Table *head, struct Table *curr){
    return head->next == curr;
}

/**
 * Print operations
 * printTable(); - Prints the current reservations in a formatted table.
 * printMenu(); - Displays the main menu options.
 */
void printTable(struct Table *head) {
    struct Table *temp = head->next;
    if (temp == NULL) {
        printf("\033[0;31mNo reservations exist.\033[0m\n");
        printf("Press Enter to continue...");
        (void)getchar();
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
    printf(subproc_errno == 0 ? "Enter your choice: " : "\033[0;31mInvalid choice! Please try again: \033[0m");
}

/**
 * Prompt operations
 * getTable(); - Prompts user for table number input.
 * getName(); - Prompts user for name input.
 * getPhone(); - Prompts user for phone number input.
 * getDate(); - Prompts user for reservation date input.
 * getTime(); - Prompts user for reservation time input.
 */
void getTable(int *table) {
    char buffer[256];

    printf("Enter table number (1-50): ");
    do {
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
    printf("Enter phone number: ");
    do {
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

/**
 * File operations
 * loadFromFile(); - Loads reservations from a file into the stack.
 * saveToFile(); - Saves current reservations to a file.
 */
void loadFromFile(struct Table *head) {
    FILE *file = fopen("dataset.txt", "r");
    if (file == NULL) {
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int table;
        char name[NAME_LEN], phone[PHONE_LEN], date[DATE_LEN], time[TIME_LEN];

        if (sscanf(line, "%d,%19[^,],%19[^,],%14[^,],%9s", 
                   &table, name, phone, date, time) != 5) {
            printf("\033[0;31mInvalid line format in file: %s\033[0m\n", line);
            continue;
        }

        push(table, name, phone, date, time, head);
    }

    fclose(file);
}

void saveToFile(struct Table *head) {
    FILE *file = fopen("dataset.txt", "w");
    if (file == NULL) {
        printf("\033[0;31mError opening file for writing!\033[0m\n");
        (void)getchar();
        return;
    }

    struct Table *temp = head->next;
    while (temp != NULL) {
        fprintf(file, "%d,%s,%s,%s,%s\n", 
                temp->table, 
                temp->name, 
                temp->phone, 
                temp->date, 
                temp->time);
        temp = temp->next;
    }

    fclose(file);
}
