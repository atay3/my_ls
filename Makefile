CC=gcc
CFLAGS=-Wall -Wextra -Werror
DEPS = my_ls.h
TARGET = my_ls
OBJ = my_ls.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

my_ls: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean $(TARGET)