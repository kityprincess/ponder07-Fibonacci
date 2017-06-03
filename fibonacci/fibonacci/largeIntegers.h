/***********************************************************************
* Header:
*    LargeIntegers
* Summary:
*    This class allows for large integers to be used via nodes.
* Author:
*     Matthew Burr, Shayla Nelson, Bryan Lopez, Kimberly Stowe
************************************************************************/

#ifndef LARGEINTEGERS_H
#define LARGEINTEGERS_H

#include "list.h"
#include <cassert>
#include <iostream>
#include <ostream>

#define MAXNODES 7

/************************************************
* LARGEINTEGERS
* A class encapsulating large integers.
***********************************************/
class LargeIntegers
{
public:
   // default & non-defualt constructors
   LargeIntegers(int numNodes = 0) : numNodes(numNodes), large(NULL) {  }

   // copy constructor
   LargeIntegers(const LargeIntegers & source);

   // assignment operator
   LargeIntegers & operator = (const LargeIntegers & rhs);

   // displays information on the screen
   friend std::ostream & operator << (std::ostream & out, const LargeIntegers & rhs);

   // add-onto operator
   friend LargeIntegers & operator += (const LargeIntegers & lhs, const LargeIntegers & rhs);

   //variables
   List <int> * large;
   int numNodes;
};

/************************************************
* LARGEINTEGERS :: COPY CONSTRUCTOR
***********************************************/
LargeIntegers::LargeIntegers(const LargeIntegers & source)
   : numNodes(0), large(NULL)
{
   this->large = source.large;

   numNodes = source.numNodes;
}

/************************************************
* LARGEINTEGERS :: Insertion Operator
* Displays the list on the screen
***********************************************/
std::ostream & operator << (std::ostream & out, const LargeIntegers & rhs)
{
   // insert , at thousands - need to iterate through 
   for (ListIterator <int> it = rhs.large.begin();
      it != rhs.large.end(); it++)
      out << *it << ",";

   out << *it << endl;

   return out;
}

/************************************************
* LARGEINTEGERS :: Add-Onto Operator
* Adds to whole numbers & puts results in this.
***********************************************/
LargeIntegers & operator += (const LargeIntegers & lhs, const LargeIntegers & rhs)
{
   //greater than modulus 1000 and less than whatever is 21
   for (ListIterator <int> it = lhs.large.begin(), ListIterator <int> it2 = rhs.large.begin();
      it != lhs.end() || it2 != rhs.end(); it++, it2++)
   {
      *it += *it2;
      if *it <= 999999999999999999999
      {
         *it / 1000 = *this;
         if *this > 0
         {
            *it % 1000 = Node<int> * newNode;
         }
         else
            *this = Node<int> * newNode;
      } 
   }
   else
      throw "ERROR: Number too large";
}

/************************************************
* LARGEINTEGERS :: Assignment Operator
* Copies one list to another
***********************************************/
LargeIntegers & LargeIntegers :: operator = (const LargeIntegers & rhs)
{
   this->large = source.large;

   numNodes = source.numNodes;

   return *this;
}

#endif // LARGEINTEGERS_H