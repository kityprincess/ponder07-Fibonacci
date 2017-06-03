/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "largeIntegers.h"
using namespace std;


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   // Start with the initial number (1) and the initial predecessor
   {
      LargeIntegers a(0);
      LargeIntegers b(0);
      LargeIntegers fib(1);

      while (number > 0)
      {
         cout << '\t' << fib << endl;
         a = b;
         b = fib;
         fib += a;

         --number;
      }
   }

   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   // your code to display the <number>th Fibonacci number
   {
      LargeIntegers a(0);
      LargeIntegers b(0);
      LargeIntegers fib(1);
      while (number > 1)
      {
         a = b;
         b = fib;
         fib += a;
         --number;
      }
      cout << '\t' << fib << endl;
   }
}


