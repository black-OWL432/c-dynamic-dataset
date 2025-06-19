/**
 * File operations
 * loadFromFile(); - Loads reservations from a file into the stack.
 * saveToFile(); - Saves current reservations to a file.
 */

#include "include/file.h"
#include "include/color.h"

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
