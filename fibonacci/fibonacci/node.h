#ifndef NODE_H
#define NODE_H

template <class T>
class Node
{
public:
   // Because it's internal to the List class, we go ahead
   // and make fields public

   // the contained data
   T data;

   // the previous node in the list
   Node * prev;

   // the next node in the list
   Node * next;

   // there is no default constructor; only a non-default
   Node(T in_data, Node * in_prev = 0, Node * in_next = 0)
      : data(in_data), prev(in_prev), next(in_next)
   {
   }
};
#endif // !NODE_H
