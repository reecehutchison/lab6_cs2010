# lab6_cs2010

Reece Hutchison.
Franco Carlnacci.
CS2010.
Lab Assignment 5.

Simulate memory allocation. Uses a free list and a allocated list, the free 
list contains the requests that will be made, and the allocated list will 
contain the current allocated memory blocks. The programs serves a first fit 
allocation style, meaning it will iterate through the free list until it finds 
a request that can fit. If no request can fit in the current moment, then then 
iteration will continue and no memory will be allocated until enough room on 
the list expires. 

make file included to build the program. Just type "make run". 
