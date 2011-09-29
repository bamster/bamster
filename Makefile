CC = gcc
CFLAGS = -Wall -g
PROG = bamster

SRCS = imageloader.cpp bamster.cpp keyLogger.cpp  game.cpp main.cpp objects.cpp
OBJS =  $(SRCS:.cpp=.o)




ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut -lGLU
endif

$(PROG):	dependencies $(OBJS) 
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS) $(LIBS)

dependencies: $(SRCS)
	$(CC) -MM $(SRCS) > dependencies


-include dependencies

all: $(PROG)

%.o :: %.cpp
	$(CC) $*.cpp -g -c



clean:
	rm -f dependencies *.o $(PROG)
