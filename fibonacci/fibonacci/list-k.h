#ifndef LIST_H
#define LIST_H

/********************************************************************
* Header:
*    LIST
* Summary:
*    Implements a list class. With acknowledgement to Nyhoff's
*    textbook for ideas around embedding the Node class and
*    approaches to handling the various push/pull functions as
*    well as other functions.
* Authors:
*    Bryan Lopez, Kimberly Stowe, Matthew Burr & Shayla Nelson
*
* Lines to check for conformity: 86  (push_back new node)
*                                96  (push_back new node)
*                                133 (push_fron new node)
*                                142 (push_back new node)
*                                148 (no exception in instructions)
*                                197 (no exception in instructions)
*********************************************************************/
#include <new>
#include <cassert>

template <class T>
class List
{
public:
   void clear();
   void push_back() throw (const char *);
   void push_front() throw (const char *);
   ListIterator remove(list <T> ::iterator & it) throw (const char *);
   T front() const throw (const char *);
   T back() const throw (const char *);

private:
   Node <T> * headNode;
   Node <T> * backNode;
   int numElements;

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
         Node * oldHead = headNode;
         headNode = headNode->next;
         delete oldHead;
      }

      // we set backNode to NULL and set our size to 0
      backNode = NULL;
      numElements = 0;

      // and make sure we're valid after all this
      assert(isValid());
   }

   /*****************************************************************************
   * LIST :: PUSH BACK
   * Pushes an item onto the back of the list.
   *****************************************************************************/
   template<class T>
   void List<T> ::push_back(T in_value) throw (const char *)
   {
      Node * newNode = NULL;

      try
      {
         if (!empty())
         {
            // If we are not empty, then we assume that backNode is a valid
            // pointer
            assert(NULL != backNode);

            newNode = new Node(in_value, backNode, NULL);
            backNode->next = newNode;
            backNode = newNode;
         }
         else
         {
            // If we _are_ empty, then we assume that backNode and headNode 
            // are both null pointers
            assert(NULL == backNode && NULL == headNode);

            newNode = new Node(in_value);
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
      assert(isValid());
   }

   /*****************************************************************************
   * LIST :: PUSH FRONT
   * Pushes an item onto the front of the list.
   *****************************************************************************/
   template<class T>
   void List<T> ::push_front(T in_value) throw (const char *)
   {
      Node * newNode = NULL;

      try
      {
         if (!empty())
         {
            // we expect that headNode is not null
            assert(NULL != headNode);

            newNode = new Node(in_value, NULL, headNode);
            headNode->prev = newNode;
            headNode = newNode;
         }
         else
         {
            // we expect that both headNode and backNode are null
            assert(NULL == headNode && NULL == back);

            newNode = new Node(in_value);
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
      assert(isValid());
   }

   /*****************************************************************************
   * LIST :: REMOVE
   * Removes an item from the list.
   *****************************************************************************/
   template<Class T>
   List<T> ::iterator List<T> ::erase(List <T> ::iterator & it) throw (const char *)
   {
      if (headNode == NULL)
         return;
      if (it == begin())
      {
         Node * newNode = headNode->next;
         delete headNode;
         headNode = newNode
      }
      else if (it != begin() || it != end())
      {
         Node * newNode = prev->next;
         prev->next = newNode->next;
         delete newNode;
      }
      else (it == end())
      {
         catch (std::bad_alloc ex)
         {
            throw "ERROR: unable to remove from an invalid location in a list";
         }
      }

   }

   /*****************************************************************************
   * LIST :: FRONT
   * Returns the item at the front of the list
   *****************************************************************************/
   template<class T>
   T List<T> ::front() const throw (const char *)
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
   T List<T> ::back() const throw (const char *)
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
}

#endif // LIST_H