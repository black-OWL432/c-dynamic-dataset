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
 * Id: 241UA24171
 * Major: CE
 * 
 * Students 3
 * Name: Maya Alysha Binti Mohd Imran
 * Id: 242UA244CD
 * Major: CE
 * 
 * Students 4
 * Name: Muhammad Nabil Hafiz Bin Salmardi
 * Id: 242UA2411J
 * Major: LE
 * 
 * Students 5
 * Name: Nur Adlina Humaira Binti Akmal
 * Id: 242UA244CU
 * Major: CE
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define clear	"\e[1;1H\e[2J"

#define nocol	"\033[0m"
#define red	"\033[0;31m"
#define green	"\033[0;32m"
#define yellow	"\033[0;33m"
#define blue	"\033[0;34m"
#define magenta	"\033[0;35m"
#define cyan	"\033[0;36m"
#define white	"\033[0;37m"

#define NAME_LEN	20
#define PHONE_LEN	20
#define DATE_LEN	15
#define TIME_LEN	10

struct Table {
	int table;
	char name[NAME_LEN];
	char phone[PHONE_LEN];
	char date[DATE_LEN];
	char time[TIME_LEN];
	struct Table *next;
};

void printTable(struct Table *);
void printMenu();
void loadFromFile(struct Table *);
void saveToFile(struct Table *);
void getTable(int *, int);
void getName(char *, int);
void getPhone(char *, int);
void getDate(char *, int);
void getTime(char *, int);
struct Table* initTableNode(int, char *, char *, char *, char *);
int push(int, char *, char *, char *, char *, struct Table *);
char * pop(struct Table *);
char empty(struct Table *, struct Table *);
int isDuplicate(struct Table *, int, char *, char *);
void query(struct Table *, int , char *, char *, char *, char *);
void sort(struct Table *);

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

					if (push(table, name, phone, date, time, head) == 0) {
						subproc_errno = 0;
						strcpy(subproc_stdout, green "Reservation added successfully\n" nocol);
					} else {
						subproc_errno = 1;
						strcpy(subproc_stderr, "A reservation already exists!");
					}
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
							sprintf(subproc_stdout, green "Reservation cancelled successfully for " cyan "%s" nocol "\n", ret);
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
				} case 5: {
					sort(head);
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

	printf(clear);
	printf(blue "Current Reservations:" nocol "\n");
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
	printf(clear);
	printf("Welcome to table reservation service, please enter your option:\n");
	printf(blue "  [1] " nocol "Make table reservation\n");
	printf(blue "  [2] " nocol "Cancel table reservation\n");
	printf(blue "  [3] " nocol "View all reservations\n");
	printf(blue "  [4] " nocol "Search reservation\n");
	printf(blue "  [5] " nocol "Sort reservations by table number\n");
	printf(blue "  [0] " nocol "Exit\n");
	if (subproc_errno != 0) {
		fprintf(stderr, red "%s\n" nocol, subproc_stderr);
	} else {
		printf("%s", subproc_stdout);
		subproc_stdout[0] = '\0';
	}
	printf("Enter your choice: ");
	subproc_errno = 0;
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
			fprintf(stderr, red "Invalid line format in file: %s\n" nocol, line);
			continue;
		}

		(void)push(table, name, phone, date, time, head);
	}

	fclose(file);
}

void saveToFile(struct Table *head) {
	FILE *file = fopen("dataset.txt", "w");
	if (file == NULL) {
		fprintf(stderr, red "Error opening file for writing!\n" nocol);
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

/**
 * Prompt operations
 * getTable(); - Prompts user for table number input.
 * getName(); - Prompts user for name input.
 * getPhone(); - Prompts user for phone number input.
 * getDate(); - Prompts user for reservation date input.
 * getTime(); - Prompts user for reservation time input.
 */

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
 * sort(); - Sort by table number by bubble sort.
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

int push(int table, char *name, char *phone, char *date, char *time, struct Table *head) {
	if (isDuplicate(head, table, date, time)) {
		return 1;
	}

	struct Table *temp;
	temp = initTableNode(table, name, phone, date, time);
	temp->next = head->next;
	head->next = temp;

	return 0;
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

	printf(clear);
	printf(blue "Search Results: \n" nocol);
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

void sort(struct Table *head) {
    if (head == NULL || head->next == NULL) return;

    int swapped;
    struct Table *ptr1;
    struct Table *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head->next;

        while (ptr1 != NULL && ptr1->next != lptr) {
            if (ptr1->table > ptr1->next->table) {
                int temp_table = ptr1->table;
                char temp_name[NAME_LEN], temp_phone[PHONE_LEN], temp_date[DATE_LEN], temp_time[TIME_LEN];
                strcpy(temp_name, ptr1->name);
                strcpy(temp_phone, ptr1->phone);
                strcpy(temp_date, ptr1->date);
                strcpy(temp_time, ptr1->time);

                ptr1->table = ptr1->next->table;
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->phone, ptr1->next->phone);
                strcpy(ptr1->date, ptr1->next->date);
                strcpy(ptr1->time, ptr1->next->time);

                ptr1->next->table = temp_table;
                strcpy(ptr1->next->name, temp_name);
                strcpy(ptr1->next->phone, temp_phone);
                strcpy(ptr1->next->date, temp_date);
                strcpy(ptr1->next->time, temp_time);

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
