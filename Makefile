CC = g++
CFLAGS = -Wall -g
PROG = bamster

SRCS = main.cpp imageloader.cpp 

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut -lGLU
endif

all: $(PROG)

$(PROG):	$(SRCS) bamster.h
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
