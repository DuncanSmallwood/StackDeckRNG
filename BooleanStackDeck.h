#ifndef BooleanStackDeck_h
#define BooleanStackDeck_h
#include <vector>
class BooleanStackDeck {
	private:
		std::vector<bool>* currDeck;
		float yesRate;
		bool yesRateIsPercentage;
		int numCards;
		
	public:
		BooleanStackDeck(const float& yesRate);
		bool getNext();
		void resetDeck();
		void resetDeck(const float& newYesRate);
	
		friend class BooleanStackDeckTests;
		inline static bool debug = false;
	
	private:
		bool checkIfYesRateIsPercentage(const float& yesRate);
		unsigned int findDeckSize(const float& yesRate);
};
#endif