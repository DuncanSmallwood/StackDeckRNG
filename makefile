Tests: BooleanStackDeck.so TestResults.o BooleanStackDeckTests.cpp Tests.cpp 
	g++ Tests.cpp TestResults.o -L. -lBooleanStackDeck -o BooleanStackDeckTest.out

TestResults.o: TestResults.h TestResults.cpp
	g++ -c TestResults.cpp

BooleanStackDeck.so: BooleanStackDeck.cpp BooleanStackDeck.h StackDeck.h StackDeck.hpp
	g++ -c -fPIC BooleanStackDeck.cpp -o libBooleanStackDeck.so

clean:
	rm *.out *.o *.gch *.so*