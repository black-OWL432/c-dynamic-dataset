/**
 * ACE6123 Algorithms and Data Structures
 * Trimester March 2025
 * Take-Home Group Assignment (30%)
 * 
 * --------------------------------------
 * 
 * Dynamic Dataset: Book Lending System
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
#include <time.h>

#define MAX_TITLE_LEN 100
#define MAX_AUTHOR_LEN 100
#define MAX_DATE_LEN 11 // YYYY-MM-DD\0

struct Book {
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    char borrowDate[MAX_DATE_LEN];
    char returnDate[MAX_DATE_LEN];
    struct Book *next;
};

struct Book *bookListHead = NULL;
struct Book* createBookNode(char *, char *, char *, char *);
void addBook(char *, char *, char *, char *);
void freeBookList(struct Book *);
void loadBooksFromFile(char *);
void saveBooksToFile(char *);
struct Book* searchBookByTitle(char *);
struct Book* searchBookByAuthor(char *);
struct Book* searchBookByTitleAndAuthor(char *, char *);
void sortBooksByTitle();
void getCurrentDate(char *, int);
void addNewBook();
void lendBook();
void returnBook();
void displayBook(struct Book *);
void displayAllBooks();
void displayMenu();
void handleUserChoice(int);

int main() {
    char dataFileName[] = "dataset.txt";

    printf("Welcome to the Simplified Book Lending System!\n");
    loadBooksFromFile(dataFileName);

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        handleUserChoice(choice);
    } while (choice != 0);

    saveBooksToFile(dataFileName);
    freeBookList(bookListHead);

    printf("Exiting Book Lending System. Goodbye!\n");
    return 0;
}

struct Book* createBookNode(char *title, char *author, char *borrow_date, char *return_date) {
    struct Book *newNode = (struct Book *)malloc(sizeof(struct Book));

    strncpy(newNode->title, title, MAX_TITLE_LEN - 1);
    newNode->title[MAX_TITLE_LEN - 1] = '\0';
    strncpy(newNode->author, author, MAX_AUTHOR_LEN - 1);
    newNode->author[MAX_AUTHOR_LEN - 1] = '\0';
    strncpy(newNode->borrowDate, borrow_date, MAX_DATE_LEN - 1);
    newNode->borrowDate[MAX_DATE_LEN - 1] = '\0';
    strncpy(newNode->returnDate, return_date, MAX_DATE_LEN - 1);
    newNode->returnDate[MAX_DATE_LEN - 1] = '\0';
    newNode->next = NULL;

    return newNode;
}

void addBook(char *title, char *author, char *borrow_date, char *return_date) {
    struct Book *existingBook = NULL;
    struct Book *current = bookListHead;
    while(current != NULL) {
        if (strcmp(current->title, title) == 0 && strcmp(current->author, author) == 0 && strcmp(current->borrowDate, "") == 0) {
            existingBook = current;
            break;
        }
        current = current->next;
    }

    if (existingBook != NULL) {
        printf("Book '%s' by '%s' already exists and is available. No new entry added.\n", title, author);
        return;
    }

    struct Book *newBook = createBookNode(title, author, borrow_date, return_date);
    if (newBook) {
        newBook->next = bookListHead;
        bookListHead = newBook;
        printf("Book '%s' by '%s' added successfully.\n", title, author);
    }
}

void freeBookList(struct Book *head) {
    struct Book *current = head;
    struct Book *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void loadBooksFromFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

    char line[2 * MAX_TITLE_LEN + 2 * MAX_DATE_LEN + 10];
    char *token;

    freeBookList(bookListHead);
    bookListHead = NULL;

    printf("Loading book data...\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        char title[MAX_TITLE_LEN];
        char author[MAX_AUTHOR_LEN];
        char borrowDate[MAX_DATE_LEN];
        char returnDate[MAX_DATE_LEN];

        token = strtok(line, ",");
        if (token) {
            strncpy(title, token, MAX_TITLE_LEN - 1);
            title[MAX_TITLE_LEN - 1] = '\0';
        }
        token = strtok(NULL, ",");
        if (token) {
            strncpy(author, token, MAX_AUTHOR_LEN - 1);
            author[MAX_AUTHOR_LEN - 1] = '\0';
        }
        token = strtok(NULL, ",");
        if (token) {
            strncpy(borrowDate, token, MAX_DATE_LEN - 1);
            borrowDate[MAX_DATE_LEN - 1] = '\0';
        }
        token = strtok(NULL, "\n");
        if (token) {
            strncpy(returnDate, token, MAX_DATE_LEN - 1);
            returnDate[MAX_DATE_LEN - 1] = '\0';
        }

        addBook(title, author, borrowDate, returnDate);
    }
    printf("Book data loaded.\n");
    fclose(file);
}

void saveBooksToFile(char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }

    struct Book *current = bookListHead;
    while (current != NULL) {
        
        fprintf(file, "%s,%s,%s,%s\n",
                current->title, current->author, current->borrowDate, current->returnDate);
        current = current->next;
    }
    printf("Book data saved to %s.\n", filename);
    fclose(file);
}

struct Book* searchBookByTitle(char *title_query) {
    struct Book *current = bookListHead;
    while (current != NULL) {
        if (strcasecmp(current->title, title_query) == 0) { 
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct Book* searchBookByAuthor(char *author_query) {
    struct Book *current = bookListHead;
    while (current != NULL) {
        if (strcasecmp(current->author, author_query) == 0) { 
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct Book* searchBookByTitleAndAuthor(char *title_query, char *author_query) {
    struct Book *current = bookListHead;
    while (current != NULL) {
        if (strcasecmp(current->title, title_query) == 0 && strcasecmp(current->author, author_query) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void sortBooksByTitle() {
    int swapped;
    struct Book *ptr1;
    struct Book *lptr = NULL;

    if (bookListHead == NULL) return;

    do {
        swapped = 0;
        ptr1 = bookListHead;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->title, ptr1->next->title) > 0) {
                char tempTitle[MAX_TITLE_LEN];
                char tempAuthor[MAX_AUTHOR_LEN];
                char tempBorrowDate[MAX_DATE_LEN];
                char tempReturnDate[MAX_DATE_LEN];

                strcpy(tempTitle, ptr1->title);
                strcpy(ptr1->title, ptr1->next->title);
                strcpy(ptr1->next->title, tempTitle);

                strcpy(tempAuthor, ptr1->author);
                strcpy(ptr1->author, ptr1->next->author);
                strcpy(ptr1->next->author, tempAuthor);

                strcpy(tempBorrowDate, ptr1->borrowDate);
                strcpy(ptr1->borrowDate, ptr1->next->borrowDate);
                strcpy(ptr1->next->borrowDate, tempBorrowDate);

                strcpy(tempReturnDate, ptr1->returnDate);
                strcpy(ptr1->returnDate, ptr1->next->returnDate);
                strcpy(ptr1->next->returnDate, tempReturnDate);

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printf("Books sorted by title.\n");
}

void getCurrentDate(char *date_str, int max_len) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(date_str, max_len, "%Y-%m-%d", tm_info);
}

void addNewBook() {
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];

    printf("Enter Book Title: ");
    fgets(title, MAX_TITLE_LEN, stdin);
    title[strcspn(title, "\n")] = '\0';

    printf("Enter Author: ");
    fgets(author, MAX_AUTHOR_LEN, stdin);
    author[strcspn(author, "\n")] = '\0';

    struct Book *found = searchBookByTitleAndAuthor(title, author);
    if (found != NULL && strcmp(found->borrowDate, "") == 0) {
        printf("Error: Book '%s' by '%s' already exists in the available inventory.\n", title, author);
        return;
    }

    addBook(title, author, "", "");
    printf("New book '%s' by '%s' added to available inventory.\n", title, author);
}

void lendBook() {
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    char currentDate[MAX_DATE_LEN];

    printf("Enter Title of the book to lend: ");
    fgets(title, MAX_TITLE_LEN, stdin);
    title[strcspn(title, "\n")] = '\0';

    printf("Enter Author of the book to lend: ");
    fgets(author, MAX_AUTHOR_LEN, stdin);
    author[strcspn(author, "\n")] = '\0';

    struct Book *bookToLend = searchBookByTitleAndAuthor(title, author);

    if (bookToLend == NULL) {
        printf("Book '%s' by '%s' not found in the system.\n", title, author);
        return;
    }

    if (strcmp(bookToLend->borrowDate, "") != 0) { 
        printf("Book '%s' by '%s' is already borrowed (borrowed on %s).\n",
               bookToLend->title, bookToLend->author, bookToLend->borrowDate);
        return;
    }

    getCurrentDate(currentDate, MAX_DATE_LEN);
    strcpy(bookToLend->borrowDate, currentDate);
    strcpy(bookToLend->returnDate, "N/A");
    printf("Book '%s' by '%s' successfully lent on %s.\n",
           bookToLend->title, bookToLend->author, bookToLend->borrowDate);
}

void returnBook() {
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    char currentDate[MAX_DATE_LEN];

    printf("Enter Title of the book to return: ");
    fgets(title, MAX_TITLE_LEN, stdin);
    title[strcspn(title, "\n")] = '\0';

    printf("Enter Author of the book to return: ");
    fgets(author, MAX_AUTHOR_LEN, stdin);
    author[strcspn(author, "\n")] = '\0';

    struct Book *bookToReturn = searchBookByTitleAndAuthor(title, author);

    if (bookToReturn == NULL) {
        printf("Book '%s' by '%s' not found in the system.\n", title, author);
        return;
    }

    if (strcmp(bookToReturn->borrowDate, "") == 0) { 
        printf("Book '%s' by '%s' is already available.\n", bookToReturn->title, bookToReturn->author);
        return;
    }

    getCurrentDate(currentDate, MAX_DATE_LEN);
    strcpy(bookToReturn->returnDate, currentDate);

    strcpy(bookToReturn->borrowDate, "");
    printf("Book '%s' by '%s' successfully returned on %s.\n",
           bookToReturn->title, bookToReturn->author, bookToReturn->returnDate);
}

void displayBook(struct Book *book) {
    if (book == NULL) return;
    printf("%-30s %-20s %-12s %-12s %s\n",
           book->title, book->author,
           strcmp(book->borrowDate, "") == 0 ? "Available" : book->borrowDate, 
           strcmp(book->returnDate, "N/A") == 0 ? "Borrowed" : book->returnDate, 
           (strcmp(book->borrowDate, "") != 0 && strcmp(book->returnDate, "N/A") == 0) ? "(CURRENTLY BORROWED)" : ""
    );
}

void displayAllBooks() {
    if (bookListHead == NULL) {
        printf("No books in the system.\n");
        return;
    }
    printf("\n--- All Books ---\n");
    printf("%-30s %-20s %-12s %-12s %s\n", "Title", "Author", "Borrowed", "Returned", "Status");
    printf("--------------------------------------------------------------------------------------\n");
    struct Book *current = bookListHead;
    while (current != NULL) {
        displayBook(current);
        current = current->next;
    }
}

void displayMenu() {
    printf("\n--- Book Lending System Menu ---\n");
    printf("1. Add New Book (to inventory)\n");
    printf("2. Lend a Book\n");
    printf("3. Return a Book\n");
    printf("4. Search Book by Title\n");
    printf("5. Search Book by Author\n");
    printf("6. Display All Books\n");
    printf("7. Sort Books by Title\n");
    printf("0. Exit\n");
}

void handleUserChoice(int choice) {
    char title_query[MAX_TITLE_LEN];
    char author_query[MAX_AUTHOR_LEN];
    struct Book *foundBook;

    switch (choice) {
        case 1: 
            addNewBook();
            break;
        case 2: 
            lendBook();
            break;
        case 3: 
            returnBook();
            break;
        case 4: 
            printf("Enter Title to search: ");
            fgets(title_query, MAX_TITLE_LEN, stdin);
            title_query[strcspn(title_query, "\n")] = '\0';
            foundBook = searchBookByTitle(title_query);
            if (foundBook) {
                printf("\nBook Found:\n");
                printf("%-30s %-20s %-12s %-12s %s\n", "Title", "Author", "Borrowed", "Returned", "Status");
                printf("--------------------------------------------------------------------------------------\n");
                displayBook(foundBook);
            } else {
                printf("Book with title '%s' not found.\n", title_query);
            }
            break;
        case 5: 
            printf("Enter Author to search: ");
            fgets(author_query, MAX_AUTHOR_LEN, stdin);
            author_query[strcspn(author_query, "\n")] = '\0';
            foundBook = searchBookByAuthor(author_query);
            if (foundBook) {
                printf("\nBook Found:\n");
                printf("%-30s %-20s %-12s %-12s %s\n", "Title", "Author", "Borrowed", "Returned", "Status");
                printf("--------------------------------------------------------------------------------------\n");
                displayBook(foundBook);
            } else {
                printf("Book by author '%s' not found.\n", author_query);
            }
            break;
        case 6: 
            displayAllBooks();
            break;
        case 7: 
            sortBooksByTitle();
            displayAllBooks();
            break;
        case 0: 
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}
