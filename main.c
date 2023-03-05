#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOK_NAME_LENGTH 150
#define MAX_AUTHOR_NAME_LENGTH 150
#define MAX_STUDENT_NAME_LENGTH 150

struct book
{
    int id;
    char name[MAX_BOOK_NAME_LENGTH];
    char author[MAX_AUTHOR_NAME_LENGTH];
    int is_issued;
    char student_name[MAX_STUDENT_NAME_LENGTH];
    int student_id;
    struct book *next;
};

struct book *head = NULL;

//function to insert 1 book at a time
void add_book()
{
    struct book *new_book = malloc(sizeof(struct book));
    printf("\t\t\t\t\tEnter book ID: ");
    scanf("%d", &new_book->id);
    printf("\t\t\t\t\tEnter book name: ");


fflush(stdin);
    gets(new_book->name);
    fflush(stdin);
    printf("\t\t\t\t\tEnter author name: ");



   gets(new_book->author);
   fflush(stdin);
    new_book->is_issued = 0;

    new_book->next = NULL;
    if (head == NULL)
    {
        head = new_book;
    }
    else
    {
        struct book *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_book;
    }
    printf("\t\t\t\t\tBook added successfully.\n");
}

//function to display all the books
void display_books()
{
    if (head == NULL)
    {

        printf("\t\t\t\t\t-------------------------\n");

        printf("\t\t\t\t\tNo books available.\n");
    }
    else
    {
        struct book *current = head;
        printf("\t\t\t\t\t-------------------------\n");

        printf("\t\t\t\t\t List of Available Books\n");

        printf("\t\t\t\t\t-------------------------\n");
        printf("\tB.ID\t\tName\t\t\tAuthor\t\t\tIssued\t\tStudent\t\tS.ID\n");
        while (current != NULL)
        {
            printf("\t%d\t\t%s\t\t%s\t\t%s\t\t%s\t\t%d\n", current->id, current->name, current->author,
                   current->is_issued ? "Yes" : "No", current->student_name, current->student_id);
            current = current->next;
        }
    }
}

//function to delte books from the list
void delete_book()
{
    if (head == NULL)
    {
        printf("\t\t\t\t\tNo books available.\n");
    }
    else
    {
        int id;
        printf("\t\t\t\t\tEnter book ID to delete: ");
        scanf("%d", &id);
        if (head->id == id)
        {
            struct book *temp = head;
            head = head->next;
            free(temp);
            printf("\t\t\t\t\tBook deleted successfully.\n");
        }
        else
        {
            struct book *current = head;
            while (current->next != NULL && current->next->id != id)
            {
                current = current->next;
            }
            if (current->next == NULL)
            {
                printf("\t\t\t\t\tBook with ID %d not found.\n", id);
            }
            else
            {
                struct book *temp = current->next;
                current->next = current->next->next;
                free(temp);
                printf("\t\t\t\t\tBook deleted successfully.\n");
            }
        }
    }
}

//function to issue specific books to a student
void issue_book()
{
    if (head == NULL)
    {
        printf("\t\t\t\t\tNo books available.\n");
    }
    else
    {
        int id;
        printf("\t\t\t\t\tEnter book ID to issue: ");
        scanf("%d", &id);
        struct book *current = head;
        while (current != NULL && current->id != id)
        {
            current = current->next;
        }
        if (current == NULL)
        {
            printf("\t\t\t\t\tBook with ID %d not found.\n", id);
        }
        else if (current->is_issued)
        {
            printf("\t\t\t\t\tBook with ID %d is already issued to %s.\n", current->id, current->student_name);
        }
        else
        {
            printf("\t\t\t\t\tEnter student name: ");
            fflush(stdin);
            gets(current->student_name);
            fflush(stdin);
            printf("\t\t\t\t\tEnter student ID: ");
            scanf("%d", &current->student_id);
            current->is_issued = 1;
            printf("\t\t\t\t\tBook issued successfully to %s with ID: %d\n", current->student_name, current->student_id);
        }
    }
}

//function when a student returns a book
void return_book()
{
    if (head == NULL)
    {
        printf("\t\t\t\t\tNo books available.\n");
    }
    else
    {
        int id;
        printf("\t\t\t\t\tEnter book ID to return: ");
        scanf("%d", &id);
        struct book *current = head;
        while (current != NULL && current->id != id)
        {
            current = current->next;
        }
        if (current == NULL)
        {
            printf("\t\t\t\t\tBook with ID %d not found.\n", id);
        }
        else if (!current->is_issued)
        {
            printf("\t\t\t\t\tBook with ID %d is not issued to anyone.\n", current->id);
        }
        else
        {
            char student_name[MAX_STUDENT_NAME_LENGTH];

            printf("\t\t\t\t\tEnter student name: ");

            scanf("%s", student_name);
            if (strcmp(current->student_name, student_name) != 0)
            {
                printf("\t\t\t\t\tBook with ID %d is not issued to %s.\n", current->id, student_name);
            }
            else
            {

                current->is_issued = 0;

                memset(current->student_name, 0, MAX_STUDENT_NAME_LENGTH);

                current->student_id = 0;
                printf("\t\t\t\t\tBook returned successfully.\n");
            }
        }
    }
}

//function to search for a specific book by its name
void search_book()
{

    struct book *temp = head;
    if (temp == NULL)
    {
        printf("No books found!\n");
        return;
    }

    char title[MAX_BOOK_NAME_LENGTH];
    printf("\t\t\t\t\tEnter Book Name You Want : ");
     fflush(stdin);
    gets(title);


    printf("\t\t\t\t\t-------------------------\n");
    printf("\t\t\t\t\tSearch Results\n");
    printf("\t\t\t\t\t-------------------------\n");

    while (temp != NULL)
    {
        if (strcmp(head->name, title) == 0)
        {
              printf("\tB.ID\t\tName\t\t\tAuthor\t\t\tIssued\t\tStudent\t\tS.ID\n");

            printf("\t%d\t\t%s\t\t%s\t\t%s\t\t%s\t\t%d\n", temp->id,  temp->name,  temp->author,
                    temp->is_issued ? "Yes" : "No",  temp->student_name,  temp->student_id);
            return;
        }
        temp = temp->next;
    }
    printf("Book not found!\n");
}

//function to write the data into a doc file
void write_data()
{

    FILE *file = fopen("book.doc", "w");
    struct book *temp = head;

    while (temp != NULL)
    {

        fprintf(file, "book id: %d ,book-name: %s, book author: %s, issued: %s,student-name:%s,student-id:%d\n",
                temp->id, temp->name, temp->author, temp->is_issued ? "Yes" : "No", temp->student_name ? temp->student_name : 0, temp->student_id ? temp->student_id : 0);
        temp = temp->next;
    }
    fclose(file);
    printf("\t\t\t\t\t-------------------------\n");
    printf("\t\t\t\t\tBook List Data Written in file.");
}
int main()
{
    int op;
    do
    {
        system("cls");
        printf("\n\t\t\t\t\tLibrary Management System\n");
        printf("\n\t\t\t\t\t-------------------------");
        printf("\n\t\t\t\t\t-------------------------");
        printf("\n\t\t\t\t\t-------------------------\n");

        printf("\t\t\t\t\t1. Insert A New Book\n");
        printf("\t\t\t\t\t2. Display All Books\n");
        printf("\t\t\t\t\t3. Search A Book By Title\n");
        printf("\t\t\t\t\t4. Delete A Book Record\n");
        printf("\t\t\t\t\t5. Issue Book To  Student\n");
        printf("\t\t\t\t\t6. Return Book\n");
        printf("\t\t\t\t\t7. Make A Booklist File\n");
        printf("\t\t\t\t\t0. Exit\n");
        printf("\n\t\t\t\t\t-------------------------\n");
        printf("\t\t\t\t\tEnter Your Choice: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            add_book();
            break;
        case 2:
            display_books();

            break;
        case 3:
            search_book();
            break;
        case 4:
            delete_book();
            break;
        case 5:
            issue_book();
            break;
        case 6:
            return_book();
            break;
        case 7:
            write_data();
            break;
        case 0:
            printf("\n\t\t\t   Thank You! This Programme was made by MD.MOMINUL ISLAM \n");

            break;
        default:
            printf("\t\t\t\t\tInvalid choice. Please try again.\n");
            break;
        }

        printf("\n\t\t\t\t\tPress Any Key to continue...");
        getch();
    } while (op != 0);
}
