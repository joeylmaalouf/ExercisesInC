/*
Code for Excercise 03 of ExercisesInC.
Joey L. Maalouf, Spring 2017
*/

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* flag for appending to files rather than overwriting */
static int append_output;
/* flag for ignoring interrupt signals */
static int ignore_interrupts;
/* integer count of how many output files there are to write to */
static int num_files;
/* integer array holding the indices of which args are output files */
static int file_indices[64];
/* string describing what behavior to use if there are output problems */
static char error_mode[12];

/* read_args: reads and parses the provided flags and arguments
 * argc: integer number of arguments provided
 * argv: array of strings representing the actual arguments
 * returns: nothing
*/
void read_args (int argc, char* argv[]) {
  int i, j;
  for (i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == '-') {
        if (strcmp(argv[i], "--append") == 0) {
          append_output = 1;
        }
        else if (strcmp(argv[i], "--ignore-interrupts") == 0) {
          ignore_interrupts = 1;
        }
        else if (strncmp(argv[i], "--output-error", 14) == 0) {
          strncpy(error_mode, argv[i][14] == '=' ? argv[i] + 15 : "warn-nopipe", 11);
          error_mode[11] = '\0';
        }
        else {
          fprintf(stderr, "Unrecognized flag: %s\n", argv[i] + 2);
          exit(1);
        }
      }
      else {
        for (j = 1; j < strlen(argv[i]); ++j) {
          switch (argv[i][j]) {
            case 'a':
              append_output = 1;
              break;
            case 'i':
              ignore_interrupts = 1;
              break;
            case 'p':
              strcpy(error_mode, "warn-nopipe");
              break;
            default:
              fprintf(stderr, "Unrecognized flag: %c\n", argv[i][j]);
              exit(1);
          }
        }
      }
    }
    else {
      file_indices[num_files++] = i;
    }
  }
}

/* tee: reads input from stdin and writes it to stdout and any given files
 * out_files: array of file pointers to the output files for writing
 * num_files: integer count of how many files there are to write to
 * returns: nothing
*/
void tee (FILE** out_files, int* num_files) {
  char c;
  int i;
  while (1) {
    c = fgetc(stdin);
    if (c == EOF) {
      break;
    }
    fprintf(stdout, "%c", c);
    for (i = 0; i < *num_files; ++i) {
      if (out_files[i] != NULL) {
        fprintf(out_files[i], "%c", c);
      }
    }
  }
}

/* main: parses input flags and outfiles, sets them up for teeing, and cleans up after
* argc: integer number of arguments provided
* argv: array of strings representing the actual arguments
 * returns: exit code
*/
int main (int argc, char* argv[]) {
  FILE** out_files;
  int i;
  append_output = 0;
  ignore_interrupts = 0;
  num_files = 0;
  memset(error_mode, '\0', 12);
  read_args(argc, argv);

  if (ignore_interrupts) {
    signal(SIGINT, SIG_IGN);
  }

  out_files = malloc(sizeof(FILE*) * num_files);
  for (i = 0; i < num_files; ++i) {
    out_files[i] = fopen(argv[file_indices[i]], append_output ? "a" : "w");
    if (out_files[i] == NULL) {
      if ((errno != EPIPE) || (strstr(error_mode, "nopipe") == NULL)) {
        if (strstr(error_mode, "exit") != NULL) {
          fprintf(stderr, "Error: failed to open: %s\n", argv[file_indices[i]]);
          exit(1);
        }
        else if (strstr(error_mode, "warn") != NULL) {
          fprintf(stderr, "Warning: failed to open: %s\n", argv[file_indices[i]]);
        }
      }
    }
  }

  tee(out_files, &num_files);

  for (i = 0; i < num_files; ++i) {
    fclose(out_files[i]);
  }
  free(out_files);

  return 0;
}

/*
Answers for Excercise 03 of ExercisesInC.
Joey L. Maalouf, Spring 2017

Reflect:
I think I had a good process for completing this assignment. I first read the
manpage for `tee`, as well as another site (GNU CoreUtils) that gave examples
of its usage with different flags. Once I had a good grasp of what `tee` and
did and how each flag changed its behavior, I wrote a placeholder for each of
the steps I identified: parsing, setup, teeing, and cleanup. Then, I went
through the list and fleshed out each step. The teeing itself was actually
simpler than parsing and dealing with each of the different flags. In fact,
I would say that what slowed me down was being so thorough with the parsing.

Compare:
The official version uses structs and enums to do options and modes much more
elegantly than my own solution. They also read from stdin more efficiently,
using a buffer of multiple characters rather than reading one at a time.
*/
