Tests: BooleanStackDeck.o TestResults.o BooleanStackDeckTests.cpp Tests.cpp 
	g++ Tests.cpp BooleanStackDeck.o TestResults.o -o BooleanStackDeckTest.out

TestResults.o: TestResults.h TestResults.cpp
	g++ -c TestResults.cpp

BooleanStackDeck.o: BooleanStackDeck.cpp BooleanStackDeck.h
	g++ -c BooleanStackDeck.cpp

clean:
	rm *.out *.o