#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* read_args: reads and parses the provided flags and arguments
 * argc: integer number of arguments provided
 * argv: array of strings representing the actual arguments
 * append_output: flag for appending to files rather than overwriting
 * ignore_interrupts: flag for ignoring interrupt signals
 * error_mode: string describing what behavior to use if there are output problems
 * file_indices: integer array holding the indices of which args are output files
 * num_files: the corresponding count of how many files there are to write to
 * returns: nothing
*/
void read_args (int argc, char* argv[], int* append_output, int* ignore_interrupts,
                /* char* error_mode, */ int* file_indices, int* num_files) {
  int i, j;
  for (i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == '-') {
        if (strcmp(argv[i], "--append") == 0) {
          *append_output = 1;
        }
        else if (strcmp(argv[i], "--ignore-interrupts") == 0) {
          *ignore_interrupts = 1;
        }
        /* else if (strncmp(argv[i], "--output-error", 14) == 0) {
          strncpy(error_mode, argv[i][14] == '=' ? argv[i] + 15 : "warn-nopipe", 11);
          error_mode[11] = '\0';
        } */
        else {
          fprintf(stderr, "Unrecognized flag: %s\n", argv[i] + 2);
          exit(1);
        }
      }
      else {
        for (j = 1; j < strlen(argv[i]); ++j) {
          switch (argv[i][j]) {
            case 'a':
              *append_output = 1;
              break;
            case 'i':
              *ignore_interrupts = 1;
              break;
            /* case 'p':
              strcpy(error_mode, "warn-nopipe");
              break; */
            default:
              fprintf(stderr, "Unrecognized flag: %c\n", argv[i][j]);
              exit(1);
          }
        }
      }
    }
    else {
      file_indices[*num_files] = i;
      ++*num_files;
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
      fprintf(out_files[i], "%c", c);
    }
  }
}

/* main: parses input flags and outfiles, sets them up for teeing, and cleans up after
* argc: integer number of arguments provided
* argv: array of strings representing the actual arguments
 * returns: exit code
*/
int main (int argc, char* argv[]) {
  int append_output = 0;
  int ignore_interrupts = 0;
  /* char error_mode[12] = ""; */
  int file_indices[32];
  int num_files = 0;
  FILE** out_files;
  int i;
  read_args(argc, argv, &append_output, &ignore_interrupts,
            /* error_mode, */ file_indices, &num_files);

  if (ignore_interrupts) {
    signal(SIGINT, SIG_IGN);
  }

  out_files = malloc(sizeof(FILE*) * num_files);
  for (i = 0; i < num_files; ++i) {
    out_files[i] = fopen(argv[file_indices[i]], append_output ? "a" : "w");
  }

  tee(out_files, &num_files);

  for (i = 0; i < num_files; ++i) {
    fclose(out_files[i]);
  }
  free(out_files);

  return 0;
}
