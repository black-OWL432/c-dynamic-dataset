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

struct Table* initTableNode(int, char *, char *, char *, char *);
int push(int, char *, char *, char *, char *, struct Table *);
char * pop(struct Table *);
char empty(struct Table *, struct Table *);
int isDuplicate(struct Table *, int, char *, char *);
void query(struct Table *, int , char *, char *, char *, char *);

#endif
