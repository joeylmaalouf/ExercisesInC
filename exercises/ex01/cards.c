/*
Code for Excercise 01 of ExercisesInC.
Joey L. Maalouf, 2017
*/

#include <stdio.h>
#include <stdlib.h>

/*
get_input: Takes in a destination array and writes
           the prompted user-given input value to it.
----
dst: destination array
----
returns: nothing
*/
void get_input (char* dst) {
  puts("Enter the card name: ");
  scanf("%2s", dst);
  /* Is there a nice way to flush any stdin leftovers? */
}

/*
get_value: Takes in a card name and converts
           it to the equivalent card value.
----
card_name: most recent card name
----
returns: corresponding card value
*/
int get_value (char* card_name) {
  switch(card_name[0]) {
    case 'K':
    case 'Q':
    case 'J':
      return 10;
    case 'A':
      return 11;
    case 'X':
      return -1;
    default:
      return atoi(card_name);
  }
}

/*
check_invalid: Takes in a card's name and value and determine
               whether they meet the validity or exit conditions.
----
card_name: most recent card name
val: most recent card value
----
returns: validity code
*/
int check_invalid (char* card_name, int val) {
  if (card_name[0] == 'X') {
    return -1;
  }
  else if ((val < 1) || (11 < val)) {
    return 0;
  }
  else {
    return 1;
  }
}

/*
update_count: Takes in a count and card value
              and updates the count if necessary.
----
count: current card count
val: most recent card value
----
returns: new card count
*/
int update_count (int count, int val) {
  if ((3 <= val) && (val <= 6)) {
    count++;
  } else if (val == 10) {
    count--;
  }
  return count;
}

/*
main: Repeatedly prompts user for a card and
      changes the counter based on the value.
----
returns: exit code
*/
int main () {
  char card_name[3];
  int count = 0;
  int val = 0;
  int valid = 1;

  while (valid != -1) {
    get_input(card_name);
    val = get_value(card_name);
    valid = check_invalid(card_name, val);
    if (valid == 1) {
      count = update_count(count, val);
      printf("Current count: %i\n", count);
    }
    else if (valid == 0) {
      puts("I don't understand that value!");
    }
  }

  return 0;
}
