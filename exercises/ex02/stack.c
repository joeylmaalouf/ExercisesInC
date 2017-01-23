/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int *foo () {
  int i;
  int array[SIZE]; /* initializes to stack memory, local to scope of `foo` */

  /* printf("%p\n", array); */

  for (i = 0; i < SIZE; ++i) {
    array[i] = 42;
  }

  return array;
}

void bar () {
  int i;
  int array[SIZE]; /* initializes to stack memory, local to scope of `bar` */

  /* printf("%p\n", array); */

  for (i = 0; i < SIZE; ++i) {
    array[i] = i;
  }
}

int main ()
{
  int i;
  int *array = foo(); /* gets pointer to what USED to be the array */
  bar();

  for (i = 0; i < SIZE; ++i) {
    printf("%d\n", array[i]);
  }

  return 0;
}

/*
Answers for Excercise 02 of ExercisesInC.
Joey L. Maalouf, Spring 2017

1.
This program seems intended to create an array (populated
with 42s), then iterate over it again and set each value to
its index, then finally print each of the values in the array.

2.
There is a warning: The `foo` function returns the address of the
local variable `array`. This means that, since `array` is initialized
in `foo`, it's generally not a good idea to return a pointer to its
address (since that part of the stack memory could be wiped as soon
as we leave the `foo` function).

3.
When run, this code prints (twice) the memory address of the array
populated by `foo` and modified by `bar`, then prints the actual
values contained within. That is, it works as expected... for now.

4.
If we comment out the print statements in `foo` and `bar`, our code
prints arbitrary values found at the now-deallocated address in memory
where the array used to live. Our code worked before because the
references to `array` in the print statements kept it alive in memory,
but without those, the array is cleared from the stack as soon as we
leave the scope of those functions.

5.
See comments above.
*/
