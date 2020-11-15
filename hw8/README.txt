HOMEWORK 8: ROPES


NAME:  < Ruchika Singh >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Shreya Barua, Jackson Rothgeb, ALAC tutors(I don't know their names) / Geeksforgeeks.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 26 >

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Copy Constructor: blanced rope- O(p*m)
extremely unbalanced rope - O(p*m) 
They would both be the same because it has to copy the longest path from root to leaf, p, no matter how unbalanced and the characters of the string passed in. For example the extremely unbalanced rope could have one letter on each leaf and it would still take that p*m to copy it.

Construct from Node*: balanced rope= O(p)
extremely unbalanced rope = O(p)
This constructor adds up the weights of the right side of the rope, but they both are O(p) even though an extremely unbalanced rope might have to go through more nodes.

Index: balanced rope-  O(p)
extremely unbalanced unbalanced rope - O(n)
The balanced rope is depending on where in the rope it is needed to be found which could be anywhere along the longest path, p. The unbalanced rope would potentially have to go through all the characters in the rope

Report: balanced rope - O(n)
extremely unbalanced rope - O(n)
They would both be the same because they are checking the the characters in the string to see if they match through index

iterator operator++: balanced rope- O(1)
extremely unbalanced rope - O(1)
It would take a constant amount of time for the iterator operator in both cases of balanced and unbalanced rope

Split: balanced rope - O(p)
extremely unbalanced rope - O(p)
The balanced rope would have to go through the original rope to the split and if it was an extremely unbalanced rope it would take just as long to go through all the nodes in the path to the lea.

Concat: balanced rope -O(p*m)
extremely unbalanced rope - O(p*m)
The concat function copies the rope passed in and adds that string to the original rope. The worst case would still result in the same because you would still have to go through the longest path and add the characters of the rope passed in to the end.  

TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?
My student test cases are to test specific cases where the variables given in the rope are not able to be done because it goes out of bounds. For example the first test is to make sure the constructor creates the size the right way so that the rope and string shouldn't match sizes. The second test is for the index to make sure that it wouldn't continue if the index didn't match. The last test is for report to see if that when it calls index and the substring it is check is out of range it won't be able to get the substring.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

