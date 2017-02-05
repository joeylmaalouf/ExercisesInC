#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_args (int argc, char* argv[], int* append_output, int* ignore_interrupts, /* char* error_mode, */ int* file_indices, int* num_files) {
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

int main (int argc, char* argv[]) {
  int append_output = 0;
  int ignore_interrupts = 0;
  /* char error_mode[12] = ""; */
  int file_indices[32];
  int num_files = 0;
  FILE** out_files;
  int i;
  read_args(argc, argv, &append_output, &ignore_interrupts, /* error_mode, */ file_indices, &num_files);

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
