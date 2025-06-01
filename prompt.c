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
#include "color.h"

void getTable(int *table, int allow_empty) {
    char buffer[256];

    printf("Enter table number (1-50): ");
    do {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || buffer[0] == '\n') {
            if (allow_empty && buffer[0] == '\n') {
                *table = 0;
                return;
            }
            fprintf(stderr, red "Invalid input! Please enter a number between 1 and 50: " nocol);
            continue;
        }

        if (sscanf(buffer, "%d", table) != 1) {
            fprintf(stderr, red "Invalid input! Please enter a number between 1 and 50: " nocol);
            continue;
        }

        if (*table <= 0 || *table > 50) {
            fprintf(stderr, red "Invalid input! Please enter a number between 1 and 50: " nocol);
            continue;
        }
        break;
    } while (1);
}

void getName(char *name, int allow_empty) {
    printf("Enter customer name: ");
    do {
        if (fgets(name, NAME_LEN, stdin) == NULL || name[0] == '\n') {
            if (allow_empty && name[0] == '\n') {
                name[0] = '\0';
                return;
            }
            fprintf(stderr, red "Invalid input! Please enter a valid name: " nocol);
            continue;
        }
        name[strcspn(name, "\n")] = 0;
    } while (strlen(name) == 0);
}

void getPhone(char *phone, int allow_empty) {
    printf("Enter phone number: ");
    do {
        if (fgets(phone, PHONE_LEN, stdin) == NULL || phone[0] == '\n') {
            if (allow_empty && phone[0] == '\n') {
                phone[0] = '\0';
                return;
            }
            fprintf(stderr, red "Invalid input! Please enter a valid phone number: " nocol);
            continue;
        }
        phone[strcspn(phone, "\n")] = 0;
    } while (strlen(phone) == 0);
}

void getDate(char *date, int allow_empty) {
    int day, month, year;
    char buffer[256];

    printf("Enter reservation date (DD-MM-YYYY): ");
    do {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || buffer[0] == '\n') {
            if (allow_empty && buffer[0] == '\n') {
                date[0] = '\0';
                return;
            }
            fprintf(stderr, red "Invalid date format! Use DD-MM-YYYY (e.g., 28-05-2025): " nocol);
            continue;
        }

        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) != 10 || buffer[2] != '-' || buffer[5] != '-') {
            fprintf(stderr, red "Invalid date format! Use DD-MM-YYYY (e.g., 28-05-2025): " nocol);
            continue;
        }

        if (sscanf(buffer, "%d-%d-%d", &day, &month, &year) != 3 || 
            month < 1 || month > 12 || day < 1 || day > 31) {
            fprintf(stderr, red "Invalid date format! Use DD-MM-YYYY (e.g., 28-05-2025): " nocol);
            continue;
        }

        strcpy(date, buffer);
        break;
    } while (1);
}

void getTime(char *time, int allow_empty) {
    int hour;
    char meridiem[3];
    char buffer[256];

    printf("Enter reservation time (12HR format, e.g., 2pm): ");
    do {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || buffer[0] == '\n') {
            if (allow_empty && buffer[0] == '\n') {
                time[0] = '\0';
                return;
            }
            fprintf(stderr, red "Invalid input! Please enter a valid time (e.g., 2pm): " nocol);
            continue;
        }

        buffer[strcspn(buffer, "\n")] = 0;

        if (sscanf(buffer, "%d%2s", &hour, meridiem) != 2 || hour < 1 || hour > 12 ||
            (strcmp(meridiem, "am") != 0 && strcmp(meridiem, "pm") != 0)) {
            fprintf(stderr, red "Invalid input! Please enter a valid time (e.g., 2pm): " nocol);
            continue;
        }

        strcpy(time, buffer);
        break;
    } while (1);
}
