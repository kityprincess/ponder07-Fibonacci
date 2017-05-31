/***********************************************************************
* Header:
*    List
* Summary:
*    This class contains a node for use in a linked-list.
* Author:
*     Matthew Burr, Shayla Nelson, Bryan Lopez, Kimberly Stowe
************************************************************************/

#ifndef LIST_H
#define LIST_H

#include "node.h"
#include <cassert>
#include <iostream>
#include "listIterator.h"

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
   List(List & source) throw (const char *);

   // destructor
   ~List();

   // assignment operator
   List <T> & operator=(const List<T> & source);

   // additional methods
   bool empty() const { return (headNode == NULL && numElements == 0); }
   int size()   { return numElements;                          }

   // clears the contents of list
   void clear();
   
   //adds a value to the back of the list 
   void push_back(const T & item) throw (const char *);

   //adds a value to the front of the list
   void push_front(const T & item) throw (const char *);

   // removes an item from a list using the iterator
   ListIterator <T> remove(ListIterator <T> & it) throw (const char *);

   // returns the front item of a list
   T & front() const throw (const char *);

   // returns the back item of a list
   T & back() const throw (const char *);

   ListIterator <T> insert(ListIterator <T> & location, T & item) throw (const char *);
   ListIterator <T> begin() const throw (const char *);
   ListIterator <T> end() const;
   ListIterator <T> rbegin();
   ListIterator <T> rend();

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
List <T> :: List(List <T> & source) throw (const char *)
    : headNode(NULL), backNode(NULL), numElements(0)
{
   // attempt to allocate
   try
   {
      headNode = new Node <T>();
      headNode->pPrev = headNode;
      headNode->pNext = headNode;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }


   // copy over the data
   for (ListIterator <T> it = source.begin();
        it != source.end();it++)
   {
      push_back(*it);
   }
}

/*******************************************
 * LIST :: ASSIGNMENT OPERATOR
 *******************************************/
template <class T>
List <T> & List <T> :: operator=(const List & source)
{
   clear();

   // copy over the data
   for (ListIterator <T> it = source.begin();
        it != source.end();it++)
   {
      //this->insert(it->data);
      push_back(*it);
   }

   return *this;
}

/*******************************************
 * LIST :: DESTRUCTOR
 *******************************************/
template <class T>
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

/*****************************************************************************
* LIST :: CLEAR
* Empty the LIST of all its contents
*****************************************************************************/
template<class T>
void List<T> ::clear()
{
   // if we're already empty, then we don't need to do anything
   if (empty())
      return;

   // otherwise, we just walk through the list deleting nodes
   // we expect that we have a non-null front at this point
   while (NULL != headNode)
   {
      Node <T> * oldHead = headNode;
      headNode = headNode->pNext;
      delete oldHead;
   }

   // we set backNode to NULL and set our size to 0
   backNode = NULL;
   numElements = 0;

   // and make sure we're valid after all this
   //assert(isValid());
}

/*****************************************************************************
* LIST :: PUSH BACK
* Pushes an item onto the back of the list.
*****************************************************************************/
template<class T>
void List<T> ::push_back(const T & in_value) throw (const char *)
{
   Node <T> * newNode = NULL;

   try
   {
      if (!empty())
      {
         // If we are not empty, then we assume that backNode is a valid
         // pointer
         assert(NULL != backNode);

         newNode = new Node <T> (in_value, backNode, NULL);
         backNode->pNext = newNode;
         backNode = newNode;
      }
      else
      {
         // If we _are_ empty, then we assume that backNode and headNode 
         // are both null pointers
         assert(NULL == backNode && NULL == headNode);

         newNode = new Node<T>(in_value);
         headNode = backNode = newNode;
      }
   }
   catch (std::bad_alloc ex)
   {
      throw "ERROR: Unable to allocate a new node for a list";
   }

   // At this point, but headNode and backNode should be non-null
   assert(NULL != backNode && NULL != headNode);

   numElements++;

   // Our number of Elements should be positive
   assert(numElements > 0);

   // as a final sanity check, we check our structure is valid
   //assert(isValid());
}

/*****************************************************************************
* LIST :: PUSH FRONT
* Pushes an item onto the front of the list.
*****************************************************************************/
template<class T>
void List<T> ::push_front(const T & in_value) throw (const char *)
{
   Node<T> * newNode = NULL;

   try
   {
      if (!empty())
      {
         // we expect that headNode is not null
         assert(NULL != headNode);

         newNode = new Node<T>(in_value, NULL, headNode);
         headNode->pPrev = newNode;
         headNode = newNode;
      }
      else
      {
         // we expect that both headNode and backNode are null
         assert(NULL == headNode && NULL == backNode);

         newNode = new Node<T>(in_value);
         headNode = backNode = newNode;
      }
   }
   catch (std::bad_alloc ex)
   {
      throw "ERROR: Unable to allocate a new node for a list";
   }

   // at this point neither headNode nor backNode should be null
   assert(NULL != headNode && NULL != backNode);

   numElements++;

   // Our number of Elements should be positive
   assert(numElements > 0);

   // and we do once last sanity check that we're valid
   //assert(isValid());
}

/*****************************************************************************
* LIST :: REMOVE
* Removes an item from the list.
*****************************************************************************/
template <class T>
ListIterator <T> List <T> ::remove(ListIterator <T> & it) throw (const char *)
{
   if (headNode == NULL)
      return;

   if (it == begin())
   {
      Node<T> * newNode = headNode->pNext;
      delete headNode;
      headNode = newNode;
   }
   else if (it != begin() || it != end())
   {
      Node * newNode = **it**prev->**it**next;
      **it**->**it**next = newNode->**it**next;
      delete newNode;
   }
   else (it == end())
      throw "ERROR: unable to remove from an invalid location in a list";
}

/*****************************************************************************
* LIST :: FRONT
* Returns the item at the front of the list
*****************************************************************************/
template<class T>
T & List<T> ::front() const throw (const char *)
{
   if (!empty())
   {
      // we expect that headNode is not null
      assert(NULL != headNode);
      return headNode->data;
   }
   else
   {
      throw "ERROR: unable to access data from an empty list";
   }
}

/*****************************************************************************
* List :: BACK
* Returns an item from the back of the list
*****************************************************************************/
template<class T>
T & List<T> ::back() const throw (const char *)
{
   if (!empty())
   {
      // we expect that backNode is not null
      assert(NULL != backNode);
      return backNode->data;
   }
   else
   {
      throw "ERROR: unable to access data from an empty list";
   }
}


/***************************************************************************
* List :: INSERT
* Inserts an item into the middle of the list
***************************************************************************/
template <class T>
ListIterator <T> List<T> ::insert(ListIterator <T> & location, T & item) throw (const char *)
{
   try
   {
      // front part
      Node * newNode = new Node <T>(item);
      Node * pPrev = location.p->pPrev;
      pPrev->pNext = newNode;
      newNode->pPrev = pPrev;

      location.p->pPrev = newNode;
      newNode->pNext = location.p;

      numElements++;
   }

   catch (std::bad_alloc ex)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   return ListIterator <T> newNode;
}

/***************************************************************************
* List :: BEGIN
* Starts at the beginning of the list
***************************************************************************/
template <class T>
ListIterator <T> List<T> ::begin() const throw (const char *)
{
   return ListIterator <T>(headNode->pNext);
}

/***************************************************************************
* List :: END
* Starts at the end of the list
***************************************************************************/
template <class T>
ListIterator <T> List <T> ::end() const
{
   return ListIterator <T>(backNode);
}

/****************************************************************************
* List :: RBEGIN
* Returns an iterator to the last element in the list
****************************************************************************/
template <class T>
ListIterator <T> List <T> ::rbegin()
{
   return ListIterator <T>(backNode->pPrev);
}

/****************************************************************************
* List :: REND
* Returns an iterator to past the front element in the list
****************************************************************************/
template <class T>
ListIterator <T> List <T> ::rend()
{
   return ListIterator <T>(headNode);
}

#endif // LIST_H