#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TITLE_LEN 100
#define MAX_AUTHOR_LEN 100
#define MAX_DATE_LEN 11 /* YYYY-MM-DD\0 */

struct Book {
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    char borrowDate[MAX_DATE_LEN];
    char returnDate[MAX_DATE_LEN];
    struct Book *next;
};

extern struct Book *bookListHead;

/* Book management functions */
struct Book* createBookNode(char *title, char *author, char *borrow_date, char *return_date);
void addBook(char *title, char *author, char *borrow_date, char *return_date);
void freeBookList(struct Book *head);

/* File operations */
void loadBooksFromFile(char *filename);
void saveBooksToFile(char *filename);

/* Search functions */
struct Book* searchBookByTitle(char *title_query);
struct Book* searchBookByAuthor(char *author_query);
struct Book* searchBookByTitleAndAuthor(char *title_query, char *author_query);

/* Book operations */
void sortBooksByTitle();
void getCurrentDate(char *date_str, int max_len);
void addNewBook();
void lendBook();
void returnBook();

/* Display functions */
void displayBook(struct Book *book);
void displayAllBooks();
void displayMenu();
void handleUserChoice(int choice);

#endif /* BOOK_H */
