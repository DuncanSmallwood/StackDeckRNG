#ifndef BooleanStackDeck_h
#define BooleanStackDeck_h
#include <vector>
#include "StackDeck.h"
class BooleanStackDeck : StackDeck<bool> {
	public:
		BooleanStackDeck(float yesRate);
		BooleanStackDeck(float likelyhoodArray[]);
		bool getNext();
		void resetDeck(float newYesRate);
	
		friend class BooleanStackDeckTests;
};
#endif