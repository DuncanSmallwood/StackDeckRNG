#ifndef BooleanStackDeck_CPP
#define BooleanStackDeck_CPP
#include "BooleanStackDeck.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

BooleanStackDeck::BooleanStackDeck(float yesRate)
	: StackDeck<bool>({true, false},
		{yesRate, StackDeck<bool>::checkIfLikelyhoodIsPercentage(yesRate) ? 100L - yesRate : 1L - yesRate}){}

BooleanStackDeck::BooleanStackDeck(float likelyhoodArray[])
	: StackDeck<bool>({true, false}, likelyhoodArray){}

void BooleanStackDeck::resetDeck(float newYesRate){
	const float usableYesRate = checkIfLikelyhoodIsPercentage(newYesRate) ? newYesRate/100 : newYesRate;
	const float newNoRate = 1L - usableYesRate;
	std::map<bool, float> *possibilitiesMap = new std::map<bool, float>();
	possibilitiesMap->insert(std::pair<bool, float>(true, usableYesRate));
	possibilitiesMap->insert(std::pair<bool, float>(false, newNoRate));
	StackDeck::resetDeck(*possibilitiesMap);
	if (possibilitiesMap){
		delete possibilitiesMap;
		possibilitiesMap = nullptr;
	}
}

#endif