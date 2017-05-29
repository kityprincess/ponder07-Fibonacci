#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "node.h"

template <class T>
class List;

template <class T>
class ListIterator
{
   friend class List<T>;

private:
   Node<T> * m_ptr;
   

public:
   ListIterator() : m_ptr(NULL) { }
   ListIterator(const Node<T> * & in_ptr)
      : m_ptr(in_ptr)
   {
   }

   bool operator == (const ListIterator<T> & rhs) const;
   bool operator != (const ListIterator<T> & rhs) const;
   ListIterator<T> & operator ++ ();
   ListIterator<T> operator ++ (int i);
   ListIterator<T> & operator -- ();
   ListIterator<T> operator -- (int i);
   T operator * () const;

};
#endif // !LISTITERATOR_H

template<class T>
inline bool ListIterator<T>::operator==(const ListIterator<T>& rhs) const
{
   return m_ptr == rhs.m_ptr;
}

template<class T>
inline bool ListIterator<T>::operator!=(const ListIterator<T>& rhs) const
{
   return !(*this == rhs);
}

template<class T>
inline ListIterator<T>& ListIterator<T>::operator++()
{
   if (NULL == m_ptr->next)
      throw "ERROR: End of iterator";

   m_ptr = m_ptr->next;
   return *this;
}

template<class T>
inline ListIterator<T> ListIterator<T>::operator++(int i)
{
   if (NULL == m_ptr->next)
      throw "ERROR: End of iterator";

   ListIterator<T> before = *this;
   ++this;
   return before;
}

template<class T>
inline ListIterator<T>& ListIterator<T>::operator--()
{
   if (NULL == m_ptr->prev)
      throw "ERROR: Start of Iterator";

   m_ptr = m_ptr->prev;
   return *this;
}

template<class T>
inline ListIterator<T> ListIterator<T>::operator--(int i)
{
   if (NULL == m_ptr->prev)
      throw "ERROR: Start of Iterator";

   ListIterator<T> before = *this;
   --this:
   return before;
}

template<class T>
inline T ListIterator<T>::operator*() const
{
   return m_ptr->data;
}
