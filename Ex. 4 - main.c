#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOK_NUM 4
#define NAME_LENGTH 200
#define AVAILABLE 10
#define NOT_AVAILABLE 20

typedef struct book {
	char name[NAME_LENGTH];
	char author[NAME_LENGTH];
	int available;
	int times_borrowed;
} Book;

int add_book(Book *array[], int count, int temp);
void return_book(Book *book1);
void take_book(Book *arr[], int count);
void print_books(Book* arr[], int count);
void quit(Book* arr[], int count);

int main()
{
	int user_in = 0;
	int count = 0;
	Book *books[BOOK_NUM] = { 0 }; /* An array of pointers */
	
	/* UI Printing */
	do
	{
		printf("-------------------------------------\nWelcome to the library\n-------------------------------------\n");
		printf("Library menu: \n");
		printf("\t1.Add a book/Return a book\n");
		printf("\t2.Take a book\n");
		printf("\t3.Print books by times borrowed from the library\n");
		printf("\t4.Quit\n");
		printf("Please choose the desired option [1-4]: ");
		scanf(" %d%*c", &user_in);
		/* End of UI */

		/* Choose relevant action based on the user's input */
		switch (user_in)
		{
		case 1:
			if (count >= BOOK_NUM) /* Check if the library is full */
			{
				printf("The library is full!\n");
				break;
			}
			char temp[NAME_LENGTH]; /* temp is the relevant input from the user */
			printf("Please enter book name: "); 
			gets(temp, NAME_LENGTH, stdin); /* Receiving book's name from the user*/
			int return_stat = 0; /* Indicates if return function has executed*/
			for (int i = 0; i < count; i++) /* Check if the book is already signed before, if so - use's return func. */
			{
				if (strcmp(books[i]->name, temp) == 0)
				{
					return_book(books[i]);
					return_stat = 1;
				}
			}
			if (return_stat == 0) /* Check if return function has executed */
			{
				add_book(books, count, temp); 
				count += 1;
				break;
			}
			break;
		case 2:
			take_book(books, count);
			break;
		case 3:
			print_books(books, count);
			break;
		case 4:
			quit(books, count);
			return 0;
		default:
			printf("Victory Royal! :) Yali & Lior & gal have been here!"); /* Error message of inserting invalid input */
			return 1;
		}
	} while ((user_in <= 4) && (user_in > 0));
}

/* Functions */

//Input arguments:
// Book *arr[] - contain array of pointers to book struct.
// count - an integer that holding the current numbers of pointers stored in the array.
// temp - the name of the book that user inserted, after checking that it is not already stored in the array.
//Return argument:
// if the memory allocation has failed - return's 1 to indicate that.
// In general, the function creating a new book (and allocate memory for it), by getting info from the user
// if succeeded - printing a success message in the end, else returning 1, to indicate the action failed.
int add_book(Book *arr[], int count, int temp)
{
	/* Add a new book */
	arr[count] = malloc(sizeof(Book)); /* Allocate memory for a new book */
	if (arr[count] == NULL) /* Actions if the memory allocation had faild */
	{
		printf("Memory allocation faild!\n");
		free(arr[count]);
		for (int i = 0; i < count; i++)
		{
			free(arr[i]);
			return 1;
		}
	}

	/* Get inputs of the new book */
	strcpy(arr[count]->name, temp);
	printf("Please enter author name: ");
	gets(temp, NAME_LENGTH, stdin); /* Receiving book author's name from the user*/
	strcpy(arr[count]->author, temp);
	arr[count]->available = AVAILABLE; /* Change the book's status */
	arr[count]->times_borrowed = 0; /* Change the amount of times borrowed status */
	printf("The book %s was successfully added!\n", &arr[count]->name);
}
//Input arguments:
// Book *book1 - a pointer to book that was added to the library before (checking whether the book is existing executed before).
// In general, the function check if a specific book is available in the library, 
// if not available - assume that the user intend to return it, else telling the user that the book has already exist.
void return_book(Book *book1)
{
	if (book1->available == AVAILABLE)
	{
		printf("This book is already in the library :)\n");
	}
	else
	{
		book1->available = AVAILABLE;
		printf("Thank you for returning the book!\n");
	}
}
//Input arguments:
// Book *arr[] - contain array of pointers to book struct.
// count - an integer that holding the current numbers of pointers stored in the array.
// In general, the function check if a specific book is available in the library, 
// if exist but not available - telling the user that the book has already borrowed.
// if exist and available - the user is borrowing the book and the function change the book's status and add 1 to times borrowed.
// if not exist - tell the user the book is not exist.
void take_book(Book *arr[], int count)
{
	char temp[NAME_LENGTH]; /* temp is the relevant input from the user */
	printf("Please enter book name: ");
	gets(temp, NAME_LENGTH, stdin);
	for (int i = 0; i < count; i++)/* Check if the book is already signed before*/
	{
		if (strcmp(arr[i]->name, temp) == 0 && arr[i]->available == AVAILABLE) /* In case that the book is exist and available */
		{
			arr[i]->available = NOT_AVAILABLE;
			arr[i]->times_borrowed += 1;
			printf("Enjoy the book!\n");
			return;
		}
		if (strcmp(arr[i]->name, temp) == 0 && arr[i]->available == NOT_AVAILABLE) /* In case that the book is exist but not available */
		{
			printf("I am sorry someone was quicker than you :(\n");
			return;
		}
		else /* In case that the book does not exist */
		{
			if (i == (count - 1))
			{
				printf("I am sorry we don't have this book.\n");
				return;
			}
		}
	}
}
//Input arguments:
// Book *arr[] - contain array of pointers to book struct.
// count - an integer that holding the current numbers of pointers stored in the array.
// In general, the function Sorting the array based on times borrowed and prints sorted list of the library's books.
void print_books(Book* arr[], int count)
{
	/* Sorting the array based on times borrowed */
	for (int i = 0; i < count - 1; i++) 
		for (int j = i + 1; j < count; j++)
		{
			if (arr[i]->times_borrowed < arr[j]->times_borrowed)
			{
				int temp;
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}

	/* Print sorted list of books */
	printf("Books available\n------------------------------------");
	for (int i = 0; i < count; i++)
	{
		printf("\nName: %s", arr[i]->name);
		printf("\nAuthor: %s\n", arr[i]->author);
		if (i != (count-1)) printf("-------------------------------------");
	}
}
//Input arguments:
// Book *arr[] - contain array of pointers to book struct.
// count - an integer that holding the current numbers of pointers stored in the array.
// In general, the function free all the memory allocated throughout the process and stops the program.
void quit(Book* arr[], int count)
{
	printf("leaving so soon?");
	for (int i = 0; i < count; i++) free(arr[i]);
}