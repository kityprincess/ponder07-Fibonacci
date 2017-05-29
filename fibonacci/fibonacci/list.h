#ifndef LIST_H
#define LIST_H


/********************************************************************
* Header:
*    LIST
* Summary:
*    Implements a List class. With acknowledgement to Nyhoff's
*    textbook for ideas around embedding the Node<T> class and
*    approaches to handling the various push/pull functions as
*    well as other functions.
* Authors:
*    Bryan Lopez, Kimberly Stowe, Matthew Burr & Shayla Nelson
*********************************************************************/
#include <new>
#include <cassert>
#include "node.h"
#include "listIterator.h"


template <class T>
class List
{
public:
   // default and non-default constructor
   List<T>(int in_capacity = 0) :
      m_capacity(in_capacity), m_size(0), m_front(0), m_back(0)
   {
   }

   // copy constructor
   List<T>(const List<T> & source);

   // destructor
   ~List()
   {
      clear();
   }

   // assignment operator
   List<T> & operator = (const List<T> & rhs);

   // indicates if the List is empty or not
   bool empty() const
   {
      return m_size == 0;
   }

   // gets the size (# of items) in the List
   int size() const
   {
      return m_size;
   }

   // gets the capacity (# of items it can hold) of the List
   // now, we don't really need capacity since we're using a linked list,
   // so if we never really keep this up-to-date until somebody asks for it
   int capacity()
   {
      // if we haven't set the capacity yet, but we have some data
      // then we initialize our capacity to 1
      if (m_capacity == 0 && m_size > 0)
         m_capacity = 1;

      // if our capacity is ever less than our size, we just double it
      // until it exceeds our size
      while (m_capacity < m_size)
         m_capacity *= 2;

      return m_capacity;
   }

   // empties the List
   void clear();

   // adds an item to the back of the List
   void push_back(T in_value);

   // adds an item to the front of the List
   void push_front(T in_value);

   // inserts an item after the iterator
   void insert(ListIterator<T> in_iterator, const T & item) { }

   // removes an item from the list
   void remove(ListIterator<T> in_iterator) { }

   // returns the item at the front of the List
   T & front() const;

   // returns the item at the back of the List
   T & back() const;

   // returns the start of a forward iterator
   ListIterator<T> begin() const;

   // returns the end of a forward iterator
   ListIterator<T> end() const;

   // returns the start of an iterator to iterate in reverse
   ListIterator<T> rbegin() const { return ListIterator<T>(); }

   // returns the end of an iterator to iterate in reverse
   ListIterator<T> rend() const { return ListIterator<T>(); }

private:
   // we can check this at any time to ensure our structure appears
   // valid -- useful for asserts
   bool isValid() const;

   // front and back nodes
   Node<T> * m_front;
   Node<T> * m_back;

   // keeping track of the size and capacity
   int m_capacity;
   int m_size;
};

/*****************************************************************************
* List :: COPY CONSTRUCTOR
* Creates a new List by copying another
*****************************************************************************/
template<class T>
inline List<T>::List(const List<T>& source)
   : m_capacity(0), m_size(0), m_front(NULL), m_back(NULL)
{
   Node<T> * ptr = source.m_front;

   // And now we just push the data onto our list one at a time
   while (ptr)
   {
      push_back(ptr->data);
      ptr = ptr->next;
   }

   // We expect our size to be the same as the source's at this point
   assert(m_size == source.m_size);

   // Make sure we're valid
   assert(isValid());
}

/*****************************************************************************
* List :: ASSIGNMENT
* Copies one deck onto another
*****************************************************************************/
template<class T>
inline List<T>& List<T>::operator=(const List<T>& rhs)
{
   // for starters, if we're copying onto ourselves, this is a noop
   if (this == &rhs)
      return *this;

   // okay, so now we clear our existing List
   clear();

   // Now we copy the old onto the new

   // The easiest way to do this is simply to walk the rhs list
   // and push them onto our own -- this may not be the most
   // efficient, but we're not dealing with a lot of data right now
   m_size = 0; // we start at zero since we're currently empty
   Node<T> * ptr = rhs.m_front;

   while (ptr)
   {
      push_back(ptr->data);
      ptr = ptr->next;
   }

   // we expect our size to be the same as the rhs size at this point
   assert(m_size == rhs.m_size);

   // lastly, we make sure we're valid
   assert(isValid());

   return *this;
}

/*****************************************************************************
* List :: CLEAR
* Empty the List of all its contents
*****************************************************************************/
template<class T>
inline void List<T>::clear()
{
   // if we're already empty, then we don't need to do anything
   if (empty())
      return;

   // otherwise, we just walk through the list deleting nodes
   // we expect that we have a non-null front at this point
   while (NULL != m_front)
   {
      Node<T> * oldFront = m_front;
      m_front = m_front->next;
      delete oldFront;
   }

   // we set m_back to NULL and set our size to 0
   m_back = NULL;
   m_size = 0;

   // and make sure we're valid after all this
   assert(isValid());
}

/*****************************************************************************
* List :: PUSH BACK
* Pushes an item onto the back of the List.
*****************************************************************************/
template<class T>
inline void List<T>::push_back(T in_value)
{
   Node<T> * newNode = NULL;

   try
   {
      if (!empty())
      {
         // If we are not empty, then we assume that m_back is a valid
         // pointer
         assert(NULL != m_back);

         newNode = new Node<T>(in_value, m_back, NULL);
         m_back->next = newNode;
         m_back = newNode;
      }
      else
      {
         // If we _are_ empty, then we assume that m_back and m_front 
         // are both null pointers
         assert(NULL == m_back && NULL == m_front);

         newNode = new Node<T>(in_value);
         m_front = m_back = newNode;
      }
   }
   catch (std::bad_alloc ex)
   {
      throw "ERROR: Unable to allocate a new buffer for List";
   }

   // At this point, but m_front and m_back should be non-null
   assert(NULL != m_back && NULL != m_front);

   m_size++;

   // Our size should be positive
   assert(m_size > 0);

   // as a final sanity check, we check our structure is valid
   assert(isValid());
}

/*****************************************************************************
* List :: PUSH FRONT
* Pushes an item onto the front of the List.
*****************************************************************************/
template<class T>
inline void List<T>::push_front(T in_value)
{
   Node<T> * newNode = NULL;

   try
   {
      if (!empty())
      {
         // we expect that m_front is not null
         assert(NULL != m_front);

         newNode = new Node<T>(in_value, NULL, m_front);
         m_front->prev = newNode;
         m_front = newNode;
      }
      else
      {
         // we expect that both m_front and m_back are null
         assert(NULL == m_front && NULL == m_back);

         newNode = new Node<T>(in_value);
         m_front = m_back = newNode;
      }
   }
   catch (std::bad_alloc ex)
   {
      throw "ERROR: Unable to allocate a new buffer for List";
   }

   // at this point neither m_front nor m_back should be null
   assert(NULL != m_front && NULL != m_back);

   m_size++;

   // size should be greater than 0
   assert(m_size > 0);

   // and we do once last sanity check that we're valid
   assert(isValid());
}

/*****************************************************************************
* List :: FRONT
* Returns the item at the front of the List
*****************************************************************************/
template<class T>
inline T & List<T>::front() const
{
   if (!empty())
   {
      // we expect that m_front is not null
      assert(NULL != m_front);
      return m_front->data;
   }
   else
   {
      throw "ERROR: unable to access data from an empty List";
   }
}

/*****************************************************************************
* List :: BACK
* Returns an item from the back of the List
*****************************************************************************/
template<class T>
inline T & List<T>::back() const
{
   if (!empty())
   {
      // we expect that m_back is not null
      assert(NULL != m_back);
      return m_back->data;
   }
   else
   {
      throw "ERROR: unable to access data from an empty List";
   }
}

template<class T>
inline ListIterator<T> List<T>::begin() const
{
   return ListIterator<T>(m_front);
}

template<class T>
inline ListIterator<T> List<T>::end() const
{
   return ListIterator<T>(m_back);
}

/*****************************************************************************
* List :: IS VALID
* Checks to see that the List is in a valid state
*****************************************************************************/
template<class T>
inline bool List<T>::isValid() const
{
   bool valid = true;

   // size should alway be positive or 0
   valid = valid && (m_size >= 0);

   // if size is 0, then our pointers should be null
   valid = valid && (m_size != 0 || (m_front == NULL && m_back == NULL));

   // if size is not zero, then our pointers should be non-null
   valid = valid && (m_size == 0 || (m_front != NULL && m_back != NULL));

   // lastly, if our size is 1, then m_front should == m_back
   valid = valid && (m_size != 1 || (m_front == m_back));

   return valid;
}


#endif // !List_H