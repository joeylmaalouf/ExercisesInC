/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


/* errno is an external global variable that contains
   error information */
extern int errno;


/* get_seconds returns the number of seconds since the
   beginning of the day, with microsecond precision */
double get_seconds() {
  struct timeval tv[1];

  gettimeofday(tv, NULL);
  return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i) {
  sleep(i);
  printf("Hello from child %d.\n", i);
  char* x = malloc(sizeof(char)); /* checking heap memory location */
  static char y = 'a'; /* checking stack memory location */
  printf("Child %d put x in the heap at %p and y in static at %p.\n",
         i, x, &y);
  free(x);
  exit(i);
}

/* main takes two parameters: argc is the number of command-line
   arguments; argv is an array of strings containing the command
   line arguments */
int main(int argc, char *argv[]) {
  int status;
  pid_t pid;
  double start, stop;
  int i, num_children;

  /* The first command-line argument is the name of the executable.
     If there is a second, it is the number of children to create. */
  if (argc == 2) {
    num_children = atoi(argv[1]);
  } else {
    num_children = 1;
  }

  /* get the start time */
  start = get_seconds();

  for (i=0; i<num_children; i++) {

    /* create a child process */
    printf("Creating child %d.\n", i);
    pid = fork();

  /* check for an error */
    if (pid == -1) {
      fprintf(stderr, "fork failed: %s\n", strerror(errno));
      perror(argv[0]);
      exit(1);
    }

  /* see if we're the parent or the child */
    if (pid == 0) {
      child_code(i);
    }
  }

  /* parent continues */
  printf("Hello from the parent.\n");
  char* x = malloc(sizeof(char)); /* checking heap memory location */
  static char y = 'a'; /* checking static memory location */
  printf("Parent put x in the heap at %p and y in static at %p.\n",
         x, &y);
  free(x);

  for (i=0; i<num_children; i++) {
    pid = wait(&status);

    if (pid == -1) {
      fprintf(stderr, "wait failed: %s\n", strerror(errno));
      perror(argv[0]);
      exit(1);
    }

    /* check the exit status of the child */
    status = WEXITSTATUS(status);
    printf("Child %d exited with error code %d.\n", pid, status);
  }
  /* compute the elapsed time */
  stop = get_seconds();
  printf("Elapsed time = %f seconds.\n", stop - start);

  exit(0);
}

/*
Answers for Excercise 09 of ExercisesInC.
Joey L. Maalouf, Spring 2017

1.
./fork <n> creates n child processes, each of which runs its code separately.
That is, /fork 3 creates 3 children, runs the parent's code, then waits on the
children to run their code, with child 0 printing and exiting instantly, child
1 printing and exiting after 1 second, child 2 printing and exiting after 2
seconds (so 1 second after child 1), etc.

2.
Initially, the children end up with the same values in their heap/static
segments as the parent. This is because when the parent process is forked,
the child becomes an exact copy, including things like memory segments.
However, because it is a copy, these segments are actually located in
different places in memory for the parent and children.
*/
