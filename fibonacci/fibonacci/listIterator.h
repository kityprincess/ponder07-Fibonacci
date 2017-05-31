#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "node.h"
// class inside my node class for listIterator

template <class T>

class ListIterator

{


public:

   // default constructor

   ListIterator() : p(NULL)
   {
   }



   // initialize to direct p to some item

   ListIterator(Node<T> * p) : p(p)
   {
   }



   // copy constructor

   ListIterator(const ListIterator & rhs)
   {
      *this = rhs;
   }



   // assignment operator

   ListIterator & operator = (const ListIterator & rhs)

   {

      this->p = rhs.p;
      return *this;

   }


   bool operator == (const ListIterator & rhs) const
   {
      return rhs.p == this->p;
   }
   // not equals operator

   bool operator != (const ListIterator & rhs) const

   {

      return rhs.p != this->p;

   }



   // dereference operator

   T & operator * ()

   {

      return p->data;

   }



   // prefix increment

   ListIterator <T> & operator ++ ()

   {

      p++;

      return *this;

   }



   // postfix increment

   ListIterator <T> operator++(int postfix)

   {

      ListIterator tmp(*this);

      p++;

      return tmp;

   }



   // prefix decrement

   ListIterator <T> & operator -- ()

   {

      p--;

      return *this;

   }



   // postfix decrement

   ListIterator <T> operator -- (int postfix)

   {

      ListIterator tmp(*this);

      p--;

      return tmp;

   }



private:

   Node<T> * p;

};

#endif
