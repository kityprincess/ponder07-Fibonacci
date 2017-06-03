###############################################################
# Program:
#     Week 07, LIST
#     Brother JonesL, CS235
# Author:
#     Matthew Burr, Shayla Nelson, Bryan Lopez & Kimberly Stowe
# Summary:
#     This program uses nodes to create doubly-linked circular
#		lists to deal with Fibonacci numbers. 
# Time:
#     Matthew Burr - hours
#	  Shayla Nelson - hours
#	  Bryan Lopez - hours
#	  Kimberly Stowe - 9 hours 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h week07.o fibonacci.o
	g++ -o a.out week07.o fibonacci.o
	tar -cf week07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week07.o       : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
week07.o: list.h week07.cpp
	g++ -c week07.cpp

fibonacci.o: fibonacci.h fibonacci.cpp 
	g++ -c fibonacci.cpp

