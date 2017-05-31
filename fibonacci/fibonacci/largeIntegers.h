///***********************************************************************
//* Header:
//*    LargeIntegers
//* Summary:
//*    This class allows for large integers to be used via nodes.
//* Author:
//*     Matthew Burr, Shayla Nelson, Bryan Lopez, Kimberly Stowe
//************************************************************************/
//
//#ifndef LARGEINTEGERS_H
//#define LARGEINTEGERS_H
//
//#include "list.h"
//#include <cassert>
//#include <iostream>
//#include <ostream>
//
//#define MAXNODES 7
//
///************************************************
//* LARGEINTEGERS
//* A class encapsulating large integers.
//***********************************************/
//class LargeIntegers
//{
//public:
//   // default & non-defualt constructors
//   LargeIntegers(int numNodes = 0) : numNodes(numNodes), large(NULL) {  }
//
//   // copy constructor
//   LargeIntegers(const LargeIntegers & source);
//
//   // insertion operator
//   ostream & operator << (ostream & out, const LargeIntegers & rhs)
//
//   // add-onto operator
//
//
//   // assignment operator
//   LargeIntegers & operator = (const LargeIntegers & rhs);
//
//   //variables
//   List int * large;
//   int numNodes;
//};
//
///************************************************
//* LARGEINTEGERS :: COPY CONSTRUCTOR
//***********************************************/
//LargeIntegers::LargeIntegers(const LargeIntergers & source)
//   : numNodes(0), large(NULL)
//{
//   // create a new head node
//   Node * num = source.headNode;
//
//   // while there's a node, copy it to the new list
//   while (num)
//   {
//      push_back(num->data);
//      num = num->next;
//   }
//
//   // make sure list sizes are the same
//   assert(numNodes == source.numNodes);
//
//   // assure we're still valid
//   assert(isValid());
//}
//
///************************************************
//* LARGEINTEGERS :: Insertion Operator
//* Displays the list on the screen
//***********************************************/
//ostream & LargeIntegers :: operator << (ostream & out, const LargeIntegers & rhs)
//{
//   // insert , at thousands - need to iterate through 
//   out << node << "," << node;
//   
//   return out;
//}
//
///************************************************
//* LARGEINTEGERS :: Add-Onto Operator
//* Adds to whole numbers & puts results in this.
//***********************************************/
//LargeIntegers & LargeIntegers :: operator += (const List large)
//{
//
//}
//
///************************************************
//* LARGEINTEGERS :: Assignment Operator
//* Copies one list to another
//***********************************************/
//LargeIntegers & LargeIntegers :: operator = (const LargeIntegers & rhs)
//{
//
//   // for starters, if we're copying onto ourselves, this is a noop
//   if (this == &rhs)
//      return *this;
//
//   // okay, so now we clear our existing list
//   clear();
//
//   // Now we copy the old onto the new
//
//   // Walk the rhs list and push them onto our own 
//   numNodes = 0; // we start at zero since we're currently empty
//   Node * num = rhs.headNode;
//
//   while (ptr)
//   {
//      push_back(num->data);
//      num = num->next;
//   }
//
//   // we expect our size to be the same as the rhs size at this point
//   assert(numNodes == rhs.numNodes);
//
//   // lastly, we make sure we're valid
//   assert(isValid());
//
//   return *this;
//}
//
//#endif // LARGEINTEGERS_H