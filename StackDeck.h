#ifndef StackDeck_h
#define StackDeck_h
#include <vector>
#include <map>

template<typename T> class StackDeck {
	private:
		std::vector<T>* currDeck;
		std::map<T, float> *possibilitiesMap;
		std::map<T, bool> *isPercentageMap;
		unsigned int numCards;
	
	public:
		StackDeck(T possibilities[], float likelyhoodArray[]);
		StackDeck(std::initializer_list<T> possiblityInitializer, float likelyhoodArray[]);
		StackDeck(std::initializer_list<T> possibilityInitializer, std::initializer_list<float> likelyhoodInitializer);
		StackDeck(std::map<T, float> possibilitiesMap);
		~StackDeck();
		T getNext();
		void resetDeck();
		void resetDeck(T possibilities[], float likelyhoodArray[]);
		void resetDeck(const std::map<T, float>& possibilitiesMap);
	
		inline static bool debug = false;
	
	protected:
		unsigned int findDeckSize(float likelyhoodArray[], unsigned int numPossibilities);
		unsigned int findDeckSize(const std::map<T, float>& possibilitiesMap);
		bool checkIfLikelyhoodIsPercentage(float likelyhood);
		std::map<T, float> constructPossibilitiesMap(T possibilities[], float likelyhoodArray[]);
		std::map<T, bool> constructIsPercentageMap(const std::map<T, float>& possibilityMap);
	
	friend class BooleanStackDeckTests;
};
#endif