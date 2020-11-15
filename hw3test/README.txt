HOMEWORK 3: RESIZABLE TABLE


NAME:  < Ruchika Singh >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Shreya Barua, Ryan Prashad, Jackson Rothgeb / cplusplus.com, stackoverflow.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 >



ORDER NOTATION:

Write each answer in terms of n = the number of rows and m = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get:  O(1)

set: O(1)

numRows: O(1)

numColumns: O(1)

push_back_row: O(mn)

push_back_column: O(mn)

pop_back_row: O(1)

pop_back_column: O(mn)

print: O(mn)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Table class design & implementation?

I used lldb and std::cout to debug my programs, mostly for any seg faults in the program that
I used to find the specific errors. I also used Valgrind to find the memory leaks in 
my program as well.


EXTRA CREDIT: 
Indicate here if you implemented push_back for multiple rows or
multiple columns and/or rewrote your code using pointers instead of
subscripts for extra credit.  Also document the order notation for
your multi-row and multi-column push_back functions.

I used the pointers instead of the subscripts in my code.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

