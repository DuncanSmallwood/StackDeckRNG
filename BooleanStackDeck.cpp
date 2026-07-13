#ifndef BooleanStackDeck_CPP
#define BooleanStackDeck_CPP
#include "BooleanStackDeck.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

BooleanStackDeck::BooleanStackDeck(const float& yesRate){
	srand(time(0));
	this->numCards = findDeckSize(yesRate);
	this->currDeck = new std::vector<bool>();
	this->yesRate = yesRate;
	this->resetDeck();
}

bool BooleanStackDeck::getNext(){
	bool result = currDeck->back();
	currDeck->pop_back();
	if (currDeck->empty()){
		this->resetDeck();
	}
	return result;
}

void BooleanStackDeck::resetDeck(){
	if(debug)
		std::cout << "(debug) deck size: " << numCards << std::endl;
	int yesCards = numCards * (checkIfYesRateIsPercentage(yesRate) ? yesRate / 100 : yesRate);
	int noCards = numCards - yesCards;
	if(debug)
		std::cout << "(debug) yesRate: " << yesRate << std::endl
			<< "(debug) yesCards: " << yesCards << std::endl
			<< "(debug) noCards: " << noCards << std::endl;
	for (int i = 0; i < numCards; ++i){
		int choose = rand() % (yesCards + noCards);
		if (choose < yesCards){
			currDeck->push_back(true);
			--yesCards;
		}
		else{
			currDeck->push_back(false);
			--noCards;
		}
		//if(debug)
		//	std::cout << "(debug) current deck size: " << currDeck->size() << std::endl;
	}
}

void BooleanStackDeck::resetDeck(const float& newYesRate){
	numCards = findDeckSize(newYesRate);
	resetDeck();
}

unsigned int BooleanStackDeck::findDeckSize(const float& yesRate){
	float decimalYesRate = checkIfYesRateIsPercentage(yesRate) ? yesRate / 100 : yesRate;
	int currTest = decimalYesRate;
	int numCards = 1;
	if (debug)
		std::cout << "(debug) currTest: " << currTest << std::endl
			<< "(debug) numCards: " << numCards << std::endl;
	while(currTest != decimalYesRate * numCards){
		numCards *= 10;
		currTest = decimalYesRate * numCards;
		if (debug)
			std::cout << "(debug) currTest: " << currTest << std::endl
			<< "(debug) numCards: " << numCards << std::endl;
	}
	return numCards;
}

bool BooleanStackDeck::checkIfYesRateIsPercentage(const float& yesRate){
	if (yesRate > 100.0f || yesRate < 0.0f){
		if (debug)
			std::cout << "(debug) yesRate(" << yesRate << ") is invalid" << std::endl;
		throw std::invalid_argument("yesRate");
	}
	return yesRate <= 1.0f ? false : true;
}

#endif