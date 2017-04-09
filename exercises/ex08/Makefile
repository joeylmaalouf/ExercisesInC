CC = gcc
COMPILE_FLAGS = -Wall
PKG_FLAGS = `pkg-config --cflags --libs glib-2.0`

# %: %.c
# 	$(CC) $^ -o $@ $(COMPILE_FLAGS) $(PKG_FLAGS)

ex_compile: ex_compile.c
	$(CC) $^ -o $@ $(COMPILE_FLAGS) $(PKG_FLAGS)

word_count: word_count.c
	$(CC) $^ -o $@ $(COMPILE_FLAGS) $(PKG_FLAGS)
