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
   List<T>() :
      m_node(NULL), m_size(0)
   {
      m_node = new Node<T>(T());
      m_node->next = m_node;
      m_node->prev = m_node;
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

   // empties the List
   void clear();

   // adds an item to the back of the List
   void push_back(T in_value);

   // adds an item to the front of the List
   void push_front(T in_value);

   // inserts an item after the iterator
   void insert(ListIterator<T> in_iterator, const T & item);

   // removes an item from the list
   void remove(ListIterator<T> & in_iterator);

   // returns the item at the front of the List
   T & front() const;

   // returns the item at the back of the List
   T & back() const;

   // returns the start of a forward iterator
   ListIterator<T> begin() const;

   // returns the end of a forward iterator
   ListIterator<T> end() const;

   // returns the start of an iterator to iterate in reverse
   ListIterator<T> rbegin() const;

   // returns the end of an iterator to iterate in reverse
   ListIterator<T> rend() const;

private:
   // we can check this at any time to ensure our structure appears
   // valid -- useful for asserts
   bool isValid() const;

   // front and back nodes
   Node<T> * m_node;

   // keeping track of the size and capacity
   int m_size;
};

/*****************************************************************************
* List :: COPY CONSTRUCTOR
* Creates a new List by copying another
*****************************************************************************/
template<class T>
inline List<T>::List(const List<T>& source)
   : m_size(0), m_node(NULL)
{
   try
   {
      m_node = new Node<T>(T());
      m_node->next = m_node;
      m_node->prev = m_node;
   }
   catch (std::bad_alloc ex)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }

   for (ListIterator<T> it = source.begin();
      it != source.end(); ++it)
   {
      push_back(*it);
   }
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
   m_size = 0;

   for (ListIterator<T> it = rhs.begin();
      it != rhs.end(); ++it)
      push_back(*it);

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

   // we could do this without using remove, of course, but we might as well
   // reuse the code we've written. Note that remove effectively moves the
   // iterator forward
   for (ListIterator<T> it = begin();
      it != end();)
      remove(it);

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
   insert(end(), in_value);
}

/*****************************************************************************
* List :: PUSH FRONT
* Pushes an item onto the front of the List.
*****************************************************************************/
template<class T>
inline void List<T>::push_front(T in_value)
{
   insert(begin(), in_value);
}

/*****************************************************************************
* List :: INSERT
* Inserts an item before the location in the list
*****************************************************************************/
template<class T>
inline void List<T>::insert(ListIterator<T> in_iterator, const T & item)
{
   Node<T> * newNode;
   
   try
   {
      newNode = new Node<T>(item);
   }
   catch (std::bad_alloc ex)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }

   Node<T> * ptr = in_iterator.m_ptr;
   
   if (NULL == ptr)
      throw "ERROR: invalid pointer";

   newNode->prev = ptr->prev;
   newNode->next = ptr;
   ptr->prev->next = newNode;
   ptr->prev = newNode;

   m_size++;
}

/*****************************************************************************
* List :: REMOVE
* Removes from the list the item pointed to by the iterator
*****************************************************************************/
template<class T>
inline void List<T>::remove(ListIterator<T> & in_iterator)
{
   if (in_iterator == end())
      throw "ERROR: unable to remove from an invalid location in a list";

   Node<T> * ptr = in_iterator.m_ptr;

   if (NULL == ptr)
      return;

   if (NULL != ptr->next)
      ptr->next->prev = ptr->prev;

   if (NULL != ptr->prev)
      ptr->prev->next = ptr->next;

   in_iterator.m_ptr = ptr->next;

   delete ptr;

   m_size--;
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
      return *(begin());
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
      return *(--end());
   }
   else
   {
      throw "ERROR: unable to access data from an empty List";
   }
}

/*****************************************************************************
* List :: BEGIN
* Returns an iterator pointing at the first node in the list
*****************************************************************************/
template<class T>
inline ListIterator<T> List<T>::begin() const
{
   return ListIterator<T>(m_node->next);
}

/*****************************************************************************
* List :: END
* Returns an iterator pointing at the end of the list
*****************************************************************************/
template<class T>
inline ListIterator<T> List<T>::end() const
{
   return ListIterator<T>(m_node);
}

template<class T>
inline ListIterator<T> List<T>::rbegin() const
{
   return --end();
}

template<class T>
inline ListIterator<T> List<T>::rend() const
{
   return --begin();
}

/*****************************************************************************
* List :: IS VALID
* Checks to see that the List is in a valid state
*****************************************************************************/
template<class T>
inline bool List<T>::isValid() const
{
   bool valid = true;

   

   return valid;
}


#endif // !List_H