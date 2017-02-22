# SoftSys Reflection 2

### Joey Maalouf

##### Sprint Reflection

This sprint, we covered many readings and got through a few of our planned features, so our overall progress went pretty well. As a group, we get more done now than we did in the first sprint, having figured out how best to divide the tasks and work together. I do feel like I'm making progress towards my learning goals; I continued to learn a lot about memory, and I now understand how Makefiles work.

##### Head First C Exercises

* [Chapter 2.5](../exercises/ex02.5/find_track.c)
* [Chapter 3](../exercises/ex03/tee.c)
* [Chapter 4](../exercises/ex04/Makefile)
* [Chapter 9](../exercises/ex09/fork.c)

##### ThinkOS Reading Questions

* [Chapter 3](../reading_questions/thinkos.md#chapter-3)
* [Chapter 4](../reading_questions/thinkos.md#chapter-4)
* [Chapter 6](../reading_questions/thinkos.md#chapter-6)

##### Exam Question

Q: (TOS4) What is the difference between an `inode` and a `FAT`? What advantages do they have over one another/which situations would favor one over the other?

A: `inode`s (or index nodes) store pointers to blocks full of pointers to other blocks, in a tree-like data structure up to four levels deep, with the actual data in the leaves. `FAT`s (or file allocation tables), on the other hand, store pointers to each cluster of data blocks in the previous cluster, in a data structure resembling a linked list. Because of the way they are structured, this makes `FAT` better for files whose contents constantly grow/shrink, since it's easy to add to/remove from the end of a linked list; however, `inode` is a better system for avoiding data loss from corrupt chunks, since any given block is less likely to lead to all of the rest of the file.
