/**
 * Prompt operations
 * getTable(); - Prompts user for table number input.
 * getName(); - Prompts user for name input.
 * getPhone(); - Prompts user for phone number input.
 * getDate(); - Prompts user for reservation date input.
 * getTime(); - Prompts user for reservation time input.
 */

#include "prompt.h"
#include "stack.h"

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
