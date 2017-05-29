/***********************************************************************
* Header:
*    List
* Summary:
*    This class contains a node for use in a linked-list.
* Author:
*
************************************************************************/

#ifndef LIST_H
#define LIST_H

#include "node.h"
#include <cassert>
#include <iostream>

/************************************************
 * LIST
 * A class encapsulating the notion of a list.
 ***********************************************/
template <class T>
class List
{
public:
   // default constructor
   List() : headNode(NULL), backNode(NULL), numElements(0) { }

   // copy constructor
   List(const List & source) throw (const char *);

   // destructor
   ~List();

   // assignment operator
   List <T> & operator=(const List<T> & source);

   // additional methods
   bool empty() { return (headNode == NULL and numElements == 0); }
   int size()   { return numElements;                          }

private:
   // member variables
   Node <T> * headNode;
   Node <T> * backNode;
   int numElements;
};

/*******************************************
 * LIST :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
List <T> :: List(const List <T> & source) throw (const char *)
    : headNode(NULL), backNode(NULL), numElements(0)
{
   // attempt to allocate
   List <T> * destination;
   try
   {
      destination = new List <T>;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }

   // copy over the data
   for (ListIterator <T> it = source.begin();
        it != source.end();it++)
   {
      destination->insert(it->data);
   }

   return destination;
}

/*******************************************
 * LIST :: ASSIGNMENT OPERATOR
 *******************************************/
template <class T>
List <T> & List <T> :: operator=(const List & source)
{
   // copy over the data
   for (ListIterator <T> it = source.begin();
        it != source.end();it++)
   {
      this->insert(it->data);
   }

   return *this;
}

/*******************************************
 * LIST :: DESTRUCTOR
 *******************************************/
List <T> :: ~List()
{
   while (headNode != NULL)
   {
      // use pDelete to hold the data to be deleted
      Node <T> * pDelete = headNode;
      headNode = headNode->pNext;
      delete pDelete;
   }
}

#endif // NODE_H
