# Makefile

# flags
CC := gcc
CFLAGS = -Wall -Wextra $(SANITIZER) -O1
LDFLAGS = $(SANITIZER)
SDL = -lSDL2
MATH = -lm -ldl
LDLIBS = $(SDL) $(MATH)

OBJ = main.o src/utils.o src/complex.o src/quaternion.o src/distance_estimator.o src/raymarch.o

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
