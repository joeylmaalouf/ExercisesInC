/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int global;

void f () {
  int x = 0;
  void *y = malloc(8);
  void *z = malloc(8);
  printf("Address of x is %p\n", &x);
  printf("Address of y is %p\n", y);
  printf("Address of z is %p\n", z);
}

int main () {
    int local = 5;
    void *p1 = malloc(128);
    void *p2 = malloc(128);

    printf("Address of main is %p\n", main);
    printf("Address of global is %p\n", &global);
    printf("Address of local is %p\n", &local);
    printf("Address of p1 is %p\n", p1);
    printf("Address of p2 is %p\n", p2);

    f();

    return 0;
}
