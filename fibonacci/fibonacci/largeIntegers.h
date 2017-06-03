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
#include <iomanip>
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
   LargeIntegers(int number = 0)
   {
      large.push_front(number);
   }

   // copy constructor
   LargeIntegers(const LargeIntegers & source);

   // assignment operator
   LargeIntegers & operator = (const LargeIntegers & rhs);

   // displays a LargeInteger
   void display(std::ostream & out) const;

   // add onto function
   void addOnto(const LargeIntegers & term);

private:

   //variables
   List <int> large;
};

/************************************************
* LARGEINTEGERS :: COPY CONSTRUCTOR
***********************************************/
LargeIntegers::LargeIntegers(const LargeIntegers & source)
{
   large = source.large;
}

/************************************************
* LARGEINTEGERS :: Insertion Operator
* Displays the list on the screen
***********************************************/
std::ostream & operator << (std::ostream & out, const LargeIntegers & rhs)
{
   rhs.display(out);

   return out;
}

/************************************************
* LARGEINTEGERS :: Add-Onto Operator
* Adds to whole numbers & puts results in this.
***********************************************/
LargeIntegers & operator += (LargeIntegers & lhs, const LargeIntegers & rhs)
{
   lhs.addOnto(rhs);
   return lhs;
}

/************************************************
* LARGEINTEGERS :: Assignment Operator
* Copies one list to another
***********************************************/
LargeIntegers & LargeIntegers :: operator = (const LargeIntegers & rhs)
{
   large = rhs.large;
   return *this;
}

/************************************************
* LARGEINTEGERS :: DISPLAY
* Writes this large integer to an output stream
***********************************************/
inline void LargeIntegers::display(std::ostream & out) const
{
   ListIterator<int> it = large.begin();

   while (it != large.end())
   {
      if (it == large.begin())
         out << *it;
      else
         out << std::setw(3) << std::setfill('0') << *it;
      
      ++it;

      if (it != large.end())
         out << ",";
   }
}

/************************************************
* LARGEINTEGERS :: Add Onto
* Adds one large integer onto this one
***********************************************/
inline void LargeIntegers::addOnto(const LargeIntegers & term)
{
   // we need a carry in case the number exceeds the max value that can fit in a node
   int carry = 0;

   ListIterator<int> myIt = large.rbegin();
   ListIterator<int> otherIt = term.large.rbegin();
 
   while (myIt != large.rend() || otherIt != term.large.rend())
   {
      if (otherIt == term.large.rend())
      {
         while (myIt != large.rend())
         {
            int sum = *myIt + carry;
            *myIt = sum % 1000;
            carry = sum / 1000;
            --myIt;
         }
         break;
      }
      else if (myIt == term.large.rend())
      {
         while (otherIt != term.large.rend())
         {
            int sum = *otherIt + carry;
            large.push_front(sum % 1000);
            carry = sum / 1000;
            --otherIt;
         }
         break;
      }
      else
      {
         int sum = *myIt + *otherIt + carry;
         *myIt = sum % 1000;
         carry = sum / 1000;
         --myIt;
         --otherIt;
      }
   }

   if (carry)
      large.push_front(carry);

   return;
}

#endif // LARGEINTEGERS_H