#ifndef StackDeck_cpp
#define StackDeck_cpp
#include "StackDeck.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <typename T>
StackDeck<T>::StackDeck(T possibilities[], float likelyhoodArray[]){
	srand(time(0));
	unsigned int numPossibilities = 0;
	for (T possibility : possibilities){
		++numPossibilities;
	}
	this->numCards = findDeckSize(likelyhoodArray, numPossibilities);
	this->currDeck = new std::vector<T>();
	this->possibilitiesMap = new std::map<T, float>(constructPossibilitiesMap(possibilities, likelyhoodArray));
	this->isPercentageMap = new std::map<T, bool>(constructIsPercentageMap(*possibilitiesMap));
	
	this->resetDeck();
}

template <typename T>
StackDeck<T>::StackDeck(std::initializer_list<T> possibilityInitializer, float likelyhoodArray[]){
	srand(time(0));
	T possibilities[possibilityInitializer.size()];
	int i = 0;
	for (T possibility : possibilityInitializer){
		possibilities[i++] = possibility;
	}
	this->numCards = findDeckSize(likelyhoodArray, possibilities.length);
	this->currDeck = new std::vector<T>();
	this->possibilitiesMap = new std::map<T, float>(constructPossibilitiesMap(possibilities, likelyhoodArray));
	this->isPercentageMap = new std::map<T, bool>(constructIsPercentageMap(*possibilitiesMap));
	
	this->resetDeck();
}

template <typename T>
StackDeck<T>::StackDeck(std::initializer_list<T> possibilityInitializer, std::initializer_list<float> likelyhoodInitializer){
	srand(time(0));
	T possibilities[possibilityInitializer.size()];
	int i = 0;
	for (T possibility : possibilityInitializer){
		possibilities[i++] = possibility;
	}
	i = 0;
	float likelyhoodArray[likelyhoodInitializer.size()];
	for (float likelyhood : likelyhoodInitializer){
		likelyhoodArray[i++] = likelyhood;
	}
	this->numCards = findDeckSize(likelyhoodArray, possibilities.length);
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
	for (typename std::map<T, float>::iterator it = possibilitiesMap.begin(); it != possibilitiesMap.end(); ++it){
		int currCards = numCards / isPercentageMap[it->first] ? it->second / 100 : it->second;
		cardsPerPossibilityMap->insert(std::pair<T, unsigned int>(it->first, currCards));
		if(debug)
			std::cout << "(" << it->first << "," << it->second <<"|" << currCards << "),";
	}
	if(debug)
		std::cout << "\b}" << std::endl;
	
	for (int i = 0; i < numCards; ++i){
		int choose = rand() % (numCards - i);
		int sum = 0;
		typename std::map<T,unsigned int>::iterator cardIterator = cardsPerPossibilityMap.begin();
		while (choose >= sum && cardIterator != cardsPerPossibilityMap.end()/*shouldn't be relavant*/){
			sum += cardIterator->second;
			++cardIterator;
		}
		currDeck->push_back(cardIterator->first);
		--cardIterator->second;
		if(debug)
			std::cout << "(debug) current deck size: " << currDeck->size() << std::endl;
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
unsigned int StackDeck<T>::findDeckSize(float likelyhoodArray[], unsigned int numPossibilities){
	int totalCards = 0;
	for (int i = 0; i < numPossibilities; ++i){
		float decimalLikelyhood = checkIfLikelyhoodIsPercentage(likelyhoodArray[i]) ? likelyhoodArray[i] / 100 : likelyhoodArray[i];
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
		totalCards += numCards;
	}
	return totalCards;
}

template <typename T>
unsigned int StackDeck<T>::findDeckSize(const std::map<T,float>& possibilitiesMap){
	std::vector<float> likelyhoodArray;
	likelyhoodArray.reserve(possibilitiesMap.size());
	for (typename std::map<T,float>::iterator it = possibilitiesMap.begin(); it != possibilitiesMap.end(); ++it){
		likelyhoodArray.insert(it->second);
	}
	
	return findDeckSize(likelyhoodArray.data(), possibilitiesMap.size());
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
std::map<T, float> StackDeck<T>::constructPossibilitiesMap(T possibilities[], float likelyhoodArray[]){
	unsigned int numPossibilities = 0;
	for (T possibilities : possibilities){
		++numPossibilities;
	}
	unsigned int numLikeyhoods = 0;
	for (float likelyhood : likelyhoodArray){
		++numLikeyhoods;
	}
	if (numPossibilities != numLikeyhoods /*&& numPossibilities - 1 != numLikeyhoods  I like this idea, but it poses alot of strange questions about valid likelyhoods*/){
		if (debug)
			std::cout << "(debug) number of Likelyhoods (" << numLikeyhoods << ") does not match the number of possibilities (" << numPossibilities << ")" << std::endl;
		throw std::invalid_argument("possibilities", "likelhoodArray");
	}
	
	std::map<T, float> possibilitiesMap;
	for (int i = 0; i < numPossibilities; ++i) {
		possibilitiesMap.insert({possibilities[i], likelyhoodArray[i]});
	}
	
	return possibilitiesMap;
}

template <typename T>
std::map<T, bool> StackDeck<T>::constructIsPercentageMap(const std::map<T, float>& possibilitiesMap){
	std::map<T, bool> isPercentageMap;
	isPercentageMap.reserve(possibilitiesMap.size());
	for (typename std::map<T, float>::iterator it = possibilitiesMap.begin(); it != possibilitiesMap.end(); ++it){
		isPercentageMap.insert(it->first, checkIfLikelyhoodIsPercentage(it->second));
	}
	return isPercentageMap;
}
#endif