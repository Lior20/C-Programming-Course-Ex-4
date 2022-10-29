# C-Programming-Course-EX.4
Ex. 4 in C Programming Language Course, Tel Aviv University

Assignment Requirements - building a library management system.

The supported actions:
- Adding a book to the library/returning a book
- Borrowing a book
- Printing all the books in the library in the appropriate order
- Exiting the program


The program will show the user the following interface, where the desired action can be selected:

--------------------------

Welcome to the library

--------------------------
Library menu:
  1. Add a book/Return a book
  2. Take a book
  3. Print books by times borrowed from the library
  4. Quit
 
 Please choose the desired option [1-4]
 
 
 General highlights:
  - It can be assumed that there are at most 4 different books in the library at any given time
  - It can be assumed that the user types correct input: strings of correct length and logical numbers.
  - Only when a new book is added that did not exist before, memory must be allocated to save the book data.
