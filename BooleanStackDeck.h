#ifndef BooleanStackDeck_h
#define BooleanStackDeck_h
#include <vector>
#include "StackDeck_impl.cpp"
class BooleanStackDeck : StackDeck<bool> {
	public:
		BooleanStackDeck(float yesRate);
		BooleanStackDeck(std::vector<float> likelyhoodArray);
		bool getNext();
		void resetDeck(float newYesRate);
	
		friend class BooleanStackDeckTests;
};
#endif