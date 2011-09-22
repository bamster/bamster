show: bamster
	./bamster


bamster: bamster.cpp
	gcc -g -o bamster bamster.cpp -lGL -lglut -lGLU
	
example: example.cpp
	gcc -g -o example example.cpp -lGL -lglut -lGLU
clean:
	rm bamster

.PHONY: clean
