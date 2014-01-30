
# library version
VERSION = 0.1

# program name
NAME = libmatrix

# flags
CPPFLAGS = -DVERSION=\"${VERSION}\"
CFLAGS = -g -std=c99 -pedantic -Wall -Wextra -pedantic -O3 ${CPPFLAGS}

# compiler and linker
CC = gcc
LD = ${CC}

HEADERS =\
	matrix.h\
	matrix_operations.h\
	matrix_manipulation.h\
	matrix_query.h


SOURCES =\
	matrix.c\
	matrix_operations.c\
	matrix_manipulation.c\
	matrix_query.c

OBJECTS = ${SOURCES:.c=.o}

all: $(NAME) clean

$(NAME): $(OBJECTS)
	ar -cvq $(NAME).a *.o
	
.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	sudo mv $(NAME).a /usr/lib/
	sudo cp $(HEADERS) /usr/include/
	rm *.o
	
	



