#ifndef StackDeck_cpp
#define StackDeck_cpp
#include "StackDeck.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <typename T>
StackDeck<T>::StackDeck(std::vector<T> possibilities, std::vector<float> likelyhoodArray){
	srand(time(0));
	this->numCards = findDeckSize(likelyhoodArray);
	this->currDeck = new std::vector<T>();
	this->possibilitiesMap = new std::map<T, float>(constructPossibilitiesMap(possibilities, likelyhoodArray));
	this->isPercentageMap = new std::map<T, bool>(constructIsPercentageMap(*possibilitiesMap));
	
	this->resetDeck();
}

template <typename T>
StackDeck<T>::StackDeck(std::initializer_list<T> possibilityInitializer, std::vector<float> likelyhoodArray){
	if (likelyhoodArray.size() != possibilityInitializer.size() /*somehow allow for an implied last likelyhood*/){
		if (debug)
			std::cout << "(debug) mismatched number of possiblities (" << possibilityInitializer.size() << ") and number of likelyhoods provided (" << likelyhoodArray.size() << ")" << std::endl;
		throw std::invalid_argument("likelyhoodArray");
	}
	srand(time(0));
	std::vector<T> possibilities(possibilityInitializer.size());
	int i = 0;
	for (T possibility : possibilityInitializer){
		possibilities[i++] = possibility;
	}
	this->numCards = findDeckSize(likelyhoodArray);
	this->currDeck = new std::vector<T>();
	this->possibilitiesMap = new std::map<T, float>(constructPossibilitiesMap(possibilities, likelyhoodArray));
	this->isPercentageMap = new std::map<T, bool>(constructIsPercentageMap(*possibilitiesMap));
	
	this->resetDeck();
}

template <typename T>
StackDeck<T>::StackDeck(std::initializer_list<T> possibilityInitializer, std::initializer_list<float> likelyhoodInitializer){
	// do a check for the size of both initializers
	srand(time(0));
	// probably possible to combine these 2 loops
	std::vector<T> possibilities(possibilityInitializer.size());
	int i = 0;
	for (T possibility : possibilityInitializer){
		possibilities[i++] = possibility;
	}
	i = 0;
	std::vector<float> likelyhoodArray(likelyhoodInitializer.size());
	for (float likelyhood : likelyhoodInitializer){
		likelyhoodArray[i++] = likelyhood;
	}
	this->numCards = findDeckSize(likelyhoodArray);
	this->currDeck = new std::vector<T>();
	this->possibilitiesMap = new std::map<T, float>(constructPossibilitiesMap(possibilities, likelyhoodArray));
	this->isPercentageMap = new std::map<T, bool>(constructIsPercentageMap(*possibilitiesMap));
	
	this->resetDeck();
}

template <typename T>
StackDeck<T>::StackDeck(std::map<T, float> possibilitiesMap){
	srand(time(0));
	this->possibilitiesMap = new std::map<T, float>(possibilitiesMap);
	this->numCards = findDeckSize(possibilitiesMap);
	this->currDeck = new std::vector<T>();
	this->isPercentageMap = new std::map<T, bool>(constructIsPercentageMap(*(this->possibilitiesMap)));
	
	this->resetDeck();
}

template <typename T>
StackDeck<T>::StackDeck(const StackDeck<T>& other){
	this->possibilitiesMap = new std::map<T, float>(*(other.possibilitiesMap));
	this->numCards = other.numCards;
	this->currDeck = new std::vector<T>(*(other.currDeck));
	this->isPercentageMap = new std::map<T, bool>(*(other.isPercentageMap));
}

template <typename T>
StackDeck<T>::~StackDeck(){
	if (currDeck) {
		delete currDeck;
		currDeck = nullptr;
	}
	if (possibilitiesMap) {
		delete possibilitiesMap;
		possibilitiesMap = nullptr;
	}
	if (isPercentageMap) {
		delete isPercentageMap;
		isPercentageMap = nullptr;
	}
}

template <typename T>
T StackDeck<T>::getNext(){
	T result = currDeck->back();
	currDeck->pop_back();
	if(currDeck->empty()){
		this->resetDeck();
	}
	return result;
}

template <typename T>
void StackDeck<T>::resetDeck(){
	currDeck->clear();
	std::map<T, unsigned int>* cardsPerPossibilityMap = new std::map<T, unsigned int>();
	if(debug)
		std::cout << "(debug) possibility map: {";
	typename std::map<T, float>::iterator possibilitiesIterator = possibilitiesMap->begin();
	typename std::map<T, bool>::iterator isPercentageIterator = isPercentageMap->begin();
	while (possibilitiesIterator != possibilitiesMap->end()){
		int currCards = isPercentageIterator->second
			? (possibilitiesIterator->second / 100) * numCards
			: possibilitiesIterator->second * numCards;
		cardsPerPossibilityMap->insert(std::pair<T, unsigned int>(possibilitiesIterator->first, currCards));
		if(debug)
			std::cout << "(" << possibilitiesIterator->first << "," << possibilitiesIterator->second <<" | " << currCards << "),";
		++possibilitiesIterator;
		++isPercentageIterator;
	}
	if(debug)
		std::cout << "\b}" << std::endl;
	
	for (int i = 0; i < numCards; ++i){
		int choose = rand() % (numCards - i);
		if(debug)
			std::cout << i << "---" << std::endl
			<< "(debug) choosen number: " << choose << std::endl;
		typename std::map<T,unsigned int>::iterator cardIterator = cardsPerPossibilityMap->begin();
		int sum = cardIterator->second;
		while (choose >= sum && cardIterator != cardsPerPossibilityMap->end()/*shouldn't be relavant*/){
			sum += cardIterator->second;
			++cardIterator;
		}
		if(debug)
			std::cout << "(debug) card to place: " << cardIterator->first << std::endl;
		currDeck->push_back(cardIterator->first);
		--cardIterator->second;
		if(debug){
			std::cout << "(debug) cards left to place: {";
			for (typename std::map<T, unsigned int>::iterator card = cardsPerPossibilityMap->begin(); card != cardsPerPossibilityMap->end(); ++card){
				std::cout << "(" << card->first << " | "  << card->second << "),";
			}
			std::cout << "\b}" << std::endl;
			std::cout << "(debug) current deck size: " << currDeck->size() << std::endl;
			std::cout << "(debug) current deck: {";
			for (T card : *currDeck)
				std::cout << card << ",";
			std::cout << "\b}" << std::endl;
		}
	}
	if (cardsPerPossibilityMap){
		delete cardsPerPossibilityMap;
		cardsPerPossibilityMap = nullptr;
	}
}

template <typename T>
void StackDeck<T>::resetDeck(const std::map<T, float>& possibilitiesMap){
	currDeck->clear();
	
}

template <typename T>
unsigned int StackDeck<T>::findDeckSize(std::vector<float> likelyhoodArray){
	int totalCards = 0;
	for (float likelyhood : likelyhoodArray){
		float decimalLikelyhood = checkIfLikelyhoodIsPercentage(likelyhood) ? likelyhood / 100 : likelyhood;
		int currTest = decimalLikelyhood;
		int numCards = 1;
		if (debug)
			std::cout << "(debug) currTest: " << currTest << std::endl
				<< "(debug) numCards: " << numCards << std::endl;
		while(currTest != decimalLikelyhood * numCards){
			numCards *= 10;
			currTest = decimalLikelyhood * numCards;
			if (debug)
				std::cout << "(debug) currTest: " << currTest << std::endl
				<< "(debug) numCards: " << numCards << std::endl;
		}
		totalCards = totalCards < numCards ? numCards : totalCards;
	}
	return totalCards;
}

template <typename T>
unsigned int StackDeck<T>::findDeckSize(const std::map<T,float>& possibilitiesMap){
	std::vector<float> likelyhoodArray(possibilitiesMap.size());
	for (typename std::map<T,float>::const_iterator it = possibilitiesMap.cbegin(); it != possibilitiesMap.cend(); ++it){
		likelyhoodArray.push_back(it->second);
	}
	
	return findDeckSize(likelyhoodArray);
}

template <typename T>
bool StackDeck<T>::checkIfLikelyhoodIsPercentage(float likelyhood){
	if (likelyhood > 100.0f || likelyhood < 0.0f){
		if (debug)
			std::cout << "(debug) Likelyhood(" << likelyhood << ") is invalid" << std::endl;
		throw std::invalid_argument("likelyhood");
	}
	return likelyhood <= 1.0f ? false : true;
}

template <typename T>
std::map<T, float> StackDeck<T>::constructPossibilitiesMap(std::vector<T> possibilities, std::vector<float> likelyhoodArray){
	std::map<T, float> possibilitiesMap;
	for (int i = 0; i < likelyhoodArray.size(); ++i) {
		possibilitiesMap.insert(std::pair<T, float>(possibilities[i], likelyhoodArray[i]));
	}
	
	return possibilitiesMap;
}

template <typename T>
std::map<T, bool> StackDeck<T>::constructIsPercentageMap(const std::map<T, float>& possibilitiesMap){
	std::map<T, bool> isPercentageMap;
	for (typename std::map<T, float>::const_iterator it = possibilitiesMap.cbegin(); it != possibilitiesMap.cend(); ++it){
		isPercentageMap.insert(std::pair<T, bool>(it->first, checkIfLikelyhoodIsPercentage(it->second)));
	}
	return isPercentageMap;
}
#endif