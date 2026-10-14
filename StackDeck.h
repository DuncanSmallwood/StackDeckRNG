#ifndef StackDeck_h
#define StackDeck_h
#include <vector>
#include <map>
#include <thread>

template<typename T> class StackDeck {
	private:
		std::vector<T>* currDeck;
		std::map<T, float> *possibilitiesMap;
		std::map<T, bool> *isPercentageMap;
		unsigned int numCards;
		std::thread *deckResetterThread;
	
	public:
		StackDeck(std::vector<T> possibilities, std::vector<float> likelyhoodArray);
		StackDeck(std::initializer_list<T> possiblityInitializer, std::vector<float> likelyhoodArray);
		StackDeck(std::initializer_list<T> possibilityInitializer, std::initializer_list<float> likelyhoodInitializer);
		StackDeck(std::map<T, float> possibilitiesMap);
		StackDeck(const StackDeck<T>& other);
		virtual ~StackDeck();
		T getNext();
		void resetDeck();
		void resetDeck(std::vector<T> possibilities, std::vector<float> likelyhoodArray);
		void resetDeck(const std::map<T, float>& possibilitiesMap);
	
		inline static bool debug = false;
	
	protected:
		unsigned int findDeckSize(std::vector<float> likelyhoodArray);
		unsigned int findDeckSize(const std::map<T, float>& possibilitiesMap);
		bool checkIfLikelyhoodIsPercentage(float likelyhood);
		std::map<T, float> constructPossibilitiesMap(std::vector<T> possibilities, std::vector<float> likelyhoodArray);
		std::map<T, bool> constructIsPercentageMap(const std::map<T, float>& possibilityMap);
	
	friend class StackDeckTests;
};
#include "StackDeck.hpp"
#endif