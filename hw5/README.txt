HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  < Ruchika Singh >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Ryan Prashad, Jackson Rothgeb, Shreya Barua / geeksforgeeks.com, cplusplus.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 12 >



TESTING & DEBUGGING STRATEGY:
For testing my functions I would go one by one and uncomment small sections of
code to test each function and then if I would get any seg faults I would turn to 
lldb to see where in my code it causes problems and then try different ways to fix it 
then test it again. For the memory leaks I used valgrind to test to for any and then I
realized that most came from my destroy_list() function so I fixed that.


ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 
The order notation is the same for UnrolledLL and dslist. size, front, and  back are all O(1) for STL lists. push_back, push_front, pop_back, pop_front is O(n), also push front is only O(1) if the list size is 1.
A worst case senario for example would be in the insert if all the nodes were full and it kept adding a value in each full node. This would cause the need for three more additional nodes,three new arrays, and for there to be many loops through each array. The average elements per node would be 2.
pop_back(): O(1)

pop_front(): O(n) 

push_back(): O(1)

push_front(): O(n)

erase(): O(n)

insert(): O(n)

size(): O(n)

front(): O(1)

back(): O(1)

EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


