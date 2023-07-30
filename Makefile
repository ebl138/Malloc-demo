CC = gcc
CFLAGS = -W -Wall
OBJ = malloc_demo
MSG = "Specify a target!"

$@: $<
	$(CC) $(CFLAGS) $< -o $@

echo:
	echo $(MSG)

clean:
	$(RM) $(OBJ)
