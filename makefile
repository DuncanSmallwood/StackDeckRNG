Tests: StackDeck.o BooleanStackDeck.o TestResults.o BooleanStackDeckTests.cpp StackDeck.cpp StackDeck.h Tests.cpp 
	g++ Tests.cpp BooleanStackDeck.o TestResults.o -o BooleanStackDeckTest.out

TestResults.o: TestResults.h TestResults.cpp
	g++ -c TestResults.cpp

BooleanStackDeck.o: BooleanStackDeck.cpp BooleanStackDeck.h StackDeck.o
	g++ -c BooleanStackDeck.cpp

StackDeck.o: StackDeck.h StackDeck.cpp StackDeck_impl.cpp
	g++ -c StackDeck_impl.cpp -o StackDeck.o

clean:
	rm *.out *.o *.gch