all : compile build run

compile:
	g++ -c Sample/sample.cpp -ISe-Lex 

build:
	g++ sample.o -ISe-Lex/ -o sample 

run:
	./sample.exe

clean:
	rm -f sampel.o
	rm -f sampel.exe
