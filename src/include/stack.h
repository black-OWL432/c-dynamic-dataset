#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>

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

struct Table* initTableNode(int table, char *name, char *phone, char *date, char *time);
void push(int table, char *name, char *phone, char *date, char *time, struct Table *head);
char * pop(struct Table *curr);
char empty(struct Table *head, struct Table *curr);
int isDuplicate(struct Table *, int, char *, char *);
void query(struct Table *, int , char *, char *, char *, char *);

#endif
