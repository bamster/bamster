CC = g++
CFLAGS = -Wall -g
PROG = bamster

SRCS = main.cpp imageloader.cpp bamster.cpp keyLogger.cpp game.cpp
OBJS =  $(SRCS:.cpp=.o)




ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut -lGLU
endif

$(PROG):	dependencies $(OBJS) 
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS) $(LIBS)

dependencies: $(SRCS)
	gcc -MM $(SRCS) > dependencies


-include dependencie

all: $(PROG)

%.o : %.cpp
	gcc $*.cpp -c



clean:
	rm -f dependencies *.o $(PROG)
