#ifndef StackDeckTests_h
#define StackDeckTests_h

// bit of a code smell here
// not sure if this needs to become a more of a wrapper? or maybe an extention?
class StackDeckTests {
	public:
		template <typename T>
		static bool debug(){
			return StackDeck<T>::debug;
		}
		template <typename T>
		static bool debug(bool showDebugs){
			StackDeck<T>::debug = showDebugs;
			return StackDeck<T>::debug;
		}
		template <typename T>
		static std::vector<T> currDeck(const StackDeck<T>& deck){
			return *(deck.currDeck);
			// really? "StackDeckTests<bool>::currDeck(testDeck).<vector funtion call>?
		}
		template <typename T>
		static std::map<T, float> possibilitiesMap(const StackDeck<T>& deck){
			return *(deck.possibilitiesMap);
		}
		template <typename T>
		static std::map<T, bool> isPercentageMap(const StackDeck<T>& deck){
			return *(deck.isPercentageMap);
		}
		template <typename T>
		static unsigned int numCards(const StackDeck<T>& deck){
			return deck.numCards;
		}
};
#endif