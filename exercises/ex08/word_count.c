#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>


// parse_file: reads the file at the given file path and
// populates the given hash table with its word counts
void parse_file (char* path, GHashTable* hash) {
  FILE* fp;
  char word[1024];
  int count;

  fp = fopen(path, "r");
  if (fp == NULL) {
    fprintf(stderr, "Please provide a valid input file.\n");
    exit(1);
  }

  while (fscanf(fp, "%s", word) != EOF) {
    count = GPOINTER_TO_INT(g_hash_table_lookup(hash, word)); // 0 if doesn't exist :)
    g_hash_table_insert(hash, strdup(word), GINT_TO_POINTER(count + 1));
  }

  fclose(fp);
}


// print_word_count: prints the number of
// occurrences of each word in the hash map
void print_word_count (gpointer key, gpointer value, gpointer data) {
  printf("count(\"%s\") = %d\n", key, GPOINTER_TO_INT(value));
}


int main (int argc, char** argv) {
  GHashTable* hash;

  if (argc < 2) {
    fprintf(stderr, "Please provide an input file.\n");
    return 1;
  }

  hash = g_hash_table_new(g_str_hash, g_str_equal);
  parse_file(argv[1], hash);
  g_hash_table_foreach(hash, print_word_count, NULL);
  return 0;
}
