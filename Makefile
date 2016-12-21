cal : Calculator.o WordParser.o
	g++ Calculator.o WordParser.o -o cal

Calculator.o : ./src/Calculator.cpp ./src/WordParser.h ./src/Token.h
	g++ -c ./src/Calculator.cpp

WordParser.o : ./src/WordParser.cpp ./src/Token.h
	g++ -c ./src/WordParser.cpp

clean :
	rm cal Calculator.o WordParser.o
