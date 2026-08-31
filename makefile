Tests: BooleanStackDeck.o TestResults.o BooleanStackDeckTests.cpp Tests.cpp 
	g++ Tests.cpp BooleanStackDeck.o TestResults.o -o BooleanStackDeckTest.out

TestResults.o: TestResults.h TestResults.cpp
	g++ -c TestResults.cpp

BooleanStackDeck.o: BooleanStackDeck.cpp BooleanStackDeck.h StackDeck.cpp StackDeck.h
	g++ -c BooleanStackDeck.cpp StackDeck.cpp

StackDeck.o: StackDeck.h StackDeck.cpp
	g++ -c StackDeck.cpp

clean:
	rm *.out *.o