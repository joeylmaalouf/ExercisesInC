# SoftSys Reflection 1

### Joey Maalouf

##### Sprint Reflection

This sprint, we made a lot of progress on the project, completing everything we had planned for our minimum viable product. We also properly laid out all of our plans on our sprint board, including the chapters we want to get through and the features we'd like to implement.

On the downside, there was some confusion in the group about actually doing the work for all of the chapters versus just reading through them, so we now have a plan for going over the chapters together and I've shifted some of my links over into the reflection for the next sprint.

Beyond that misunderstanding, I think we used EduScrum fairly effectively; the sprint cycles let us block out categories of features that are similar and that it makes sense to implement together. One or two of our planned features were more complex than estimated, so we just slid them back into the backlog for a future sprint so we could focus on the MVP.

##### Head First C Exercises

* [Chapter 1](../exercises/ex01/cards.c)
* [Chapter 2](../exercises/ex02/stack.c)

##### ThinkOS Reading Questions

* [Chapter 1](../reading_questions/thinkos.md#chapter-1)
* [Chapter 2](../reading_questions/thinkos.md#chapter-2)

##### Exam Question

Question:

The following code contains 3 errors. For each error, state what's going wrong, when it would affect the program (compile- or run-time), and how to fix it.

```c
#include <stdio.h>
#include <stdlib.h>

/* reverses the first n elements in arr */
void reverse (int* arr, int n) {
  int i = 0;
  int j = n - 1;
  int tmp;
  while (i < j) {
    tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
    ++i;
    --j;
  }
}

int main (int argc, char* argv[]) {
  int count, i;
  int arr;

  printf("Enter the length of the integer array:\n");
  scanf("%d", &count);
  arr = calloc(count, sizeof(int));
  if (arr == NULL)
    fprintf(stderr, "Error: failed to allocate enough memory.\n");
    return 1;

  printf("Enter the elements of the array, separated by spaces:\n");
  for (i = 0; i < count; ++i) {
    scanf("%d", &arr[i]);
  }

  reverse(arr, count);

  for (i = 0; i < count; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  return 0;
}
```

Answer:

1. Line 20.
  * What should be a pointer to an array is declared as just a single integer.
  * Compile-time (errors and warnings).
  * Change `int arr;` to `int* arr;`.

2. Lines 54-56.
  * The return statement isn't included inside the conditional block.
  * Run-time (return early).
  * Add curly brackets around lines 55 and 56.

3. Lines 24, 42.
  * The program doesn't free the allocated memory.
  * Run-time (memory leak).
  * Add `free(arr);` above `return 0;`.
