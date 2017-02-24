/*  Test code for the functions in rand.c

    Copyright 2016 Allen B. Downey
    License: MIT License https://opensource.org/licenses/MIT
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <unistd.h>

#include "rand.h"

/* Get the total of user time and system time used by this process.
 */
double get_seconds() {
  double user, sys;
  struct rusage r;

  getrusage(RUSAGE_SELF, &r);

  user = r.ru_utime.tv_sec * 1000.0 + r.ru_utime.tv_usec / 1000.0;
  sys = r.ru_stime.tv_sec * 1000.0 + r.ru_stime.tv_usec / 1000.0;

  // printf("%lf\n", user);

  return user+sys;
}

/* Compute the total time used by a function.

iters: number of times to call the function
func: function to call
 */
double time_func(int iters, double(*func)())
{
  int i;
  double t0, t1;

  srandom(time(NULL));

  t0 = get_seconds();
  for (i=0; i<iters; i++) {
    func();
  }
  t1 = get_seconds();
  return t1 - t0;
}


int main(int argc, char *argv[])
{
  double time;
  int iters = 100000000;

  // time = time_func(iters, dummy);
  // printf("%f ms \t dummy\n", time);
  //
  // time = time_func(iters, dummy2);
  // printf("%f ms \t dummy2\n", time);
  //
  // time = time_func(iters, random_float);
  // printf("%f ms \t random_float\n", time);
  //
  // time = time_func(iters, my_random_float);
  // printf("%f ms \t my_random_float\n", time);
  //
  // time = time_func(iters, my_random_float2);
  // printf("%f ms \t my_random_float2\n", time);

  time = time_func(iters, random_double);
  printf("%f ms \t random_double\n", time);

  time = time_func(iters, my_random_double);
  printf("%f ms \t my_random_double\n", time);

  return 0;
}
