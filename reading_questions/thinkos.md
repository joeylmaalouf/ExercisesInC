## Chapter 1


### Compilation

1) Give an example of a feature common in interpreted languages that is rare in compiled languages.

Dynamic types.

2) Name two advantages of static typing over dynamic typing.

* You can tell at a glance what the format of a given variable should be.
* Type checks happen at compile time instead of run time, so running is faster.

3) Give an example of a static semantic error.

If a function is defined to take an `int`, and it's given a `char`, that's a static semantic error.

4) What are two reasons you might want to turn off code optimization?

* Optimization can sometimes cause subtle bugs to [dis]appear, making debugging difficult.
* Optimization can increase compile time.

5) When you run `gcc` with `-S`, why might the results look different on different computers?

`gcc -S` generates assembly code, and different computers might run on different architectures.

6) If you spell a variable name wrong, or if you spell a function name wrong, the error messages you get might look very different. Why?

The error for a misspelled variable is an `undeclared identifier`, because the compiler couldn't find that identifier (the misspelled variable name) declared anywhere in the code. Meanwhile, a misspelled function actually gives just a warning at first; an `implicit declaration` warning, because it hasn't yet found a declaration for that function, but it might be okay with it being declared later in the code. Then comes the actual error, an `undefined reference`, because it found no reference to this misspelled function defined anywhere.

7) What is a segmentation fault?

Reading from or writing to an invalid location in memory.


## Chapter 2


### Processes

1) Give a real-world example of virtualization (ideally not one of the ones in the book).

When I go on Amazon, all I see is a list of products, but not all of these items are sold by Amazon themselves; a lot are sold by third-party retailers. I don't necessarily care about who actually made the products, because they all get routed through Amazon for me to buy.

2) What is the difference between a program and a process?

A process is an environment that runs a program in isolation. A program is just text/code, whereas a process contains the program, data, states, etc.

3) What is the primary purpose of the process abstraction? What illusion does the process abstraction create?

It allows programmers to write code without worrying about things like interruptions or offset memory; the OS uses abstraction to create the illusion of an uninterrupted process with dedicated memory.

4) What is the kernel?

The OS core, which controls important operations like threading.

5) What is a daemon?

A background process that runs OS services.


## Chapter 3


### Virtual memory

1) The Georgian alphabet has 33 letters. How many bit are needed to specify a letter?

6.

2) In the UTF-16 character encoding, the binary representation of a character can take up to 32 bits.
Ignoring the details of the encoding scheme, how many different characters can be represented?

4294967296.

3) What is the difference between "memory" and "storage" as defined in Think OS?

Memory = RAM, storage = HDD/SSD.

4) What is the difference between a GiB and a GB? What is the percentage difference in their sizes?

GiB = gibibyte = 2^30 bytes, GB = gigabyte = 10^9 bytes. 1 GiB is 7.37% larger than 1 GB.

5) How does the virtual memory system help isolate processes from each other?

It gives different processes different mappings/translations between the virtual and physical address spaces, so that no process can ever access another's data.

6) Why do you think the stack and the heap are usually located at opposite ends of the address space?

They both can expand in size, so to minimize the possibility of collision, the stack sits at the top and grows down while the heap sits at the bottom and grows up.

7) What Python data structure would you use to represent a sparse array?

A `dict`, because if you use `dict.get(key, 0)` to access keys (indices, probably), it will return the correct value for keys that have been set and `0` for keys that haven't been set, which seems like good behavior for a sparse array (with a few nonzero values and many zero values).

8) What is a context switch?

A tool that lets the OS interrupt a currently running process, save its state, and switch processes.

9) In this directory, you should find a subdirectory named `aspace` that contains `aspace.c`. Run it on your computer and compare your results to mine.

Your results:
```
Address of main   is 0x      40057c
Address of global is 0x      60104c
Address of local  is 0x7fffd26139c4
Address of p      is 0x     1c3b010
```
My results:
```
Address of main   is 0x      40057d
Address of global is 0x      60104c
Address of local  is 0x7ffd9b47da64
Address of p      is 0x     16d9010
```

10) Add a second call to `malloc` and check whether the heap on your system grows up (toward larger addresses).

It grows up.

11) Add a function that prints the address of a local variable, and check whether the stack grows down.

It grows down.

12) Choose a random number between 1 and 32, and allocate two chunks with that size.
How much space is there between them? Hint: Google knows how to subtract hexadecimal numbers.

0x20 (32 in decimal) bytes.


## Chapter 4


### Files and file systems

1) What abstractions do file systems provide? Give an example of something that is logically
true about files systems but not true of their implementations.

File systems allow programmers to have a consistent abstraction of how the files are stored, for more convenient access. File systems themselves use bytes, whereas their implementations convert that to block-based storage.

2) What information do you imagine is stored in an `OpenFileTableEntry`?

* address of file
* file's open mode flag
* current position in file

3) What are some of the ways operating systems deal with the relatively slow performance of persistent storage?

* switch over to working on other processes while they wait
* predictively pre-fetch blocks into memory to save later calls
* use a cache/buffer to minimize the number of times they read from/write to storage

4) Suppose your program writes a file and prints a message indicating that it is done writing.
Then a power cut crashes your computer. After you restore power and reboot the computer, you find that the
file you wrote is not there. What happened?

The data was likely in a buffer, ready to be written to file, but the power cut came before the buffer contents were actually transferred to disk.

5) Can you think of one advantage of a File Allocation Table over a UNIX inode? Or an advantage of a inode over a FAT?

* FAT > inode: easier to add/remove blocks at the end of a file (pointed to by the last in the list), for when the contents grow/shrink
* inode > FAT: less likely to lose the rest of a file if one block is corrupted

6) What is overhead? What is fragmentation?

Storage overhead is space used to store the data structures that hold metadata and other non-content information. Fragmentation is when blocks are left partially or fully unused, wasting the excess space.

7) Why is the "everything is a file" principle a good idea? Why might it be a bad idea?

Good:

* it makes programming consistent for files, pipes, stdin/stdout, sockets, etc.

Bad:

* it could hide or abstract away information that might be important or useful for working with individual structures that aren't actually files

If you would like to learn more about file systems, a good next step is to learn about journaling file systems.
Start with [this Wikipedia article](https://en.wikipedia.org/wiki/Journaling_file_system), then
[Anatomy of Linux Journaling File Systems](http://www.ibm.com/developerworks/library/l-journaling-filesystems/index.html).
Also consider reading [this USENIX paper](https://www.usenix.org/legacy/event/usenix05/tech/general/full_papers/prabhakaran/prabhakaran.pdf).


## Chapter 5


### Bits and bytes

1) Suppose you have the value 128 stored as an unsigned 8-bit number. What happens if you convert
it to a 16-bit number and accidentally apply sign extension?

`0b10000000` (`128`) -> `0b1111111110000000` (`65408`).

2) Write a C expression that computes the two's complement of 12 using the XOR bitwise operator.
Try it out and confirm that the result is interpreted as -12.

```
(12      ^ 0b11111) + 1
(0b01100 ^ 0b11111) + 1
 0b10011            + 1
 0b10100
-12
```

3) Can you guess why IEEE floating-point uses biased integers to represent the exponent rather than a
sign bit or two's complement?

They're more easily comparable, since the other two would register negative numbers as larger than positive ones.

4) Following the example in Section 5.4, write the 32-bit binary representation of -13 in single precision
IEEE floating-point. What would you get if you accidentally interpreted this value as an integer?

```
-13
0b10011
0b1.0011*2^4
(0)(4+127)(0b0011)
0b01000001100110000000000000000000
1100480512
```

5) Write a function that takes a string and converts from lower-case to upper-case by flipping the sixth bit.
As a challenge, you can make a faster version by reading the string 32 or 64 bits at a time, rather than one
character at a time. This optimization is made easier if the length of the string is a multiple of 4 or 8 bytes.

``` c
char* to_upper (char* lower) {
  int i;
  for (i = 0; lower[i] != '\0'; ++i) {
    if ((97 <= lower[i]) && (lower[i] <= 122)) {
      lower[i] &= 0b11011111;
    }
  }
  return lower;
}
```

## Chapter 6


### Memory management

1) Which memory management functions would you expect to take constant time? Which ones take time proportional to the size of the allocated chunk?

* Constant: `free`

* Proportional: `malloc` (proportional to number of free chunks), `calloc` (proportional to number and size of free chunks), `realloc` (proportional to size of old chunks)

2) For each of the following memory errors, give an example of something that might go wrong:

a) Reading from unallocated memory.

Reads an arbitrary value from the location, or segfault.

b) Writing to unallocated memory.

Overwrites whatever was at the location, or segfault.

c) Reading from a freed chunk.

Possibly nothing, possibly (a).

d) Writing to a freed chunk.

Possibly nothing, possibly (b).

e) Failing to free a chunk that is no longer needed.

Memory leak; system could eventually run out of memory, causing `malloc` to fail and most things to crash.


3) Run

`ps aux --sort rss`

to see a list of processes sorted by RSS, which is "resident set size", the amount of physical
memory a process has. Which processes are using the most memory?

* `chrome`
* `compiz`
* `sublime_text`

4) What's wrong with allocating a large number of small chunks? What can you do to mitigate the problem?

There's a non-trivial amount of overhead attached to each chunk, so it wouldn't be very space efficient. To fix this, we can use arrays instead.

If you want to know more about how malloc works, read
[Doug Lea's paper about dlmalloc](http://gee.cs.oswego.edu/dl/html/malloc.html)



## Chapter 7


### Caching

1) What happens if a program writes a new value into the program counter?

2) What is the fundamental problem caches are meant to solve?

3) If cache access time is 1 ns and memory access time is 10 ns, what is the average
access time of a program with hit rate 50%? How about 90%?

4) The book gives several examples of programming language features, like loops, that tend
to improve locality in the access pattern of instructions and/or data. Can you think of other examples?
Or counter-examples that might decrease locality?

5) If you refactor a program to improve locality, would you say the program is "cache aware"? Why not?

6) See if you can estimate the cost of a memory cache by comparing the prices of two similar CPUs with
different cache sizes.

7) Why are cache policies generally more complex at the bottom of the memory hierarchy?

8) Can you think of a strategy operating systems could use to avoid thrashing or recover when it occurs?

Run the cache code on your laptop or another computer and see if you can infer the cache size and block size.
If you can find the technical specifications for your computer, see if your inferences are right.

1) In this directory you should find a subdirectory named `cache` that contains `cache.c` and supporting files. Read `cache.c`, then run `make` and `./cache`.

2) Run `python graph_data.py` to see the results. What can you infer about the cache structure on your computer?


## Chapter 8


### Multitasking

1) What is the kernel's most basic task?

2) When an interrupt occurs, what part of the hardware state is saved by hardware?

3) What is the difference between an interrupt and a context switch?

4) Give an example of an event that might cause a process to move from the blocked to the ready state.

5) Why might a scheduler want to give higher priority to an I/O bound process?

When I make French toast, I usually make a batch of 12 slices. But my griddle only has room for 8 slices. Each piece of toast has to cook for 5 minutes on each side. How can I schedule 12 slices onto 8 "cores" to minimize the elapsed time to cook all 12 slices? (Note: this question is not hypothetical; this is really how I make French toast.)



## Chapter 9


### POSIX threads and mutexes

As you read Chapter 9, you should compile and run the example code. By the nature of multi-threaded programs, you results will probably be different from mine, possibly in interesting ways.

1) Why does each thread have its own stack?

2) What does the `gcc flag -lpthread` do?

3) What does the argument of `pthread_exit` do?

4) Normally the same thread that created a thread also waits to join it. What happens if another thread tries to join a thread it did not create?

5) What goes wrong if several threads try to increment a shared integer at the same time?

6) What does it mean to "lock a mutex"?



## Chapter 10


### Condition variables

1) What does it mean to say that a data structure is thread safe?

2) In the circular buffer implementation of a queue, why is the maximum number of elements in the queue `n-1`,
if `n` is the size of the array?

3) If there is no mutex to protect the queue, give an example of a sequence of steps that could leave
the queue in an inconsistent state.

4) When a thread calls cond_wait, why does it have to unlock the mutex before blocking?

5) When a thread returns from cond_wait, what do we know is definitely true? What do we think is probably true?

6) What happens if you signal a condition variable when there are no waiting threads?

7) Do you have to lock the mutex to signal a condition variable?

8) Does the condition have to be true when you signal a condition variable?



## Chapter 11


### Semaphores in C
