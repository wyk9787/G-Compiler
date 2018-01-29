all: compiler

compiler: compiler.cpp
	g++ compiler.cpp -o compiler

clean:
	rm -f *.o *~ core*
