# Makefile

# flags
CC := gcc
CFLAGS = -Wall -Wextra $(SANITIZER) -O1
LDFLAGS = $(SANITIZER)
SDL = -lSDL2
MATH = -lm -ldl
LDLIBS = $(SDL) $(MATH)

OBJ = main.o utils.o quaternion.o distance_estimator.o

#SANITIZER = -fsanitize=address
#SANITIZER =

.PHONY: all clean
.DEFAULT_GOAL := main

all: main

main: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@ $(SDL) $(MATH) && (./$@ ; echo Exit status: $$? ; true) || echo Makefile: failed to build, launcing target aborted

clean:
	rm -rvf main $(OBJ)

# END
