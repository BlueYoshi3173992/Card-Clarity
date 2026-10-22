#include <math.h>
#include <stdlib.h>
#include <windows.h>

#include "logger.h"
#include "cards.h"

const wchar_t* networkNames[] = {
	L"Visa",
	L"Mastercard",
	L"American Express",
	L"Discover"
};

const wchar_t* rewardTitles[] = {
	L"Cash Back",
	L"Points",
	L"Miles"
};

Card cardA = { 0 };
Card cardB = { 0 };
Card cardC = { 0 };
Card cardD = { 0 };
Card cardE = { 0 };

Card registerCard(char* issuer, enum Network network, int annualFee, enum Reward reward, double rate) {
	Card card = { 0 };

	GUID guid = { 0 };
	if (!SUCCEEDED(CoCreateGuid(&guid))) {
		logMessage("GUID could not be created.", ERROR);
	}
	card.guid = guid;

	card.issuer = issuer;
	card.network = network;
	card.annualFee = annualFee;
	card.reward = reward;
	card.rate = rate;
	return card;
}

LPCWSTR getGUIDAsLPCWSTR(GUID guid) {
	LPWSTR buf = (LPWSTR)malloc(37 * sizeof(wchar_t));

	swprintf_s(
		buf, 
		37, 
		L"%08lx-%04hx-%04hx-%02hhx%02hhx-%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx",
		guid.Data1,
		guid.Data2,
		guid.Data3,
		guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3], guid.Data4[4],
		guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	return buf;
}

LPCWSTR getBaseInfo(Card card) {
	LPWSTR buf = (LPWSTR)malloc(256 * sizeof(wchar_t));
	
	swprintf_s(
		buf,
		256,
		L"Issuer = [%hs]\nNetwork = [%ls]\nReward Type = [%ls]\nAnnual Fee = [%d]\nBase Rate = [%.2f]",
		card.issuer ? card.issuer : "Unknown",
		networkNames[card.network],
		rewardTitles [card.reward] ,
		card.annualFee,
		card.rate
	);

	return buf;
}

LPCWSTR getMultiplierInfo(Card card) {
	LPWSTR buf = (LPWSTR)malloc(256 * sizeof(wchar_t));

	swprintf_s(
		buf,
		256,
		L"Airlines Multiplier = [%.2f]\nStores Multiplier = [%.2f]\nServices Multiplier = [%.2f]\n10$ Service purchase = [%.2f]",
		card.multipliers[AIRLINES].multiplier,
		card.multipliers[STORES].multiplier,
		card.multipliers[SERVICES].multiplier,
		calculateReward(card, SERVICES, 10)
	);

	return buf;
}

void addMultiplier(Card* card, enum MerchantCategory category, double multiplier) {
	Multiplier newMultiplier = { 0 };
	newMultiplier.category = category;
	newMultiplier.multiplier = multiplier;
	
	card->multipliers[category] = newMultiplier;
}

double calculateReward(Card card, enum MerchantCategory category, double amount) {
	double baseReward = amount * (card.rate/100);
	double multiplier = card.multipliers[category].multiplier;
	return baseReward * (1 + multiplier / 100);
}

Card* testGetCard(int id) {
	switch (id) {
	case (0):
		return &cardA;
	case (1):
		return &cardB;
	case (2):
		return &cardC;
	case (3):
		return &cardD;
	case (4):
		return &cardE;
	default:
		return &cardA;
	}
}

void initTestCards() {
	cardA = registerCard("Chase", VISA, 95, REWARD_POINTS, 1.25);
	addMultiplier(&cardA, AIRLINES, 5.0);
	addMultiplier(&cardA, STORES, 3.0);
	addMultiplier(&cardA, SERVICES, 2.0);

	cardB = registerCard("American Express", AMEXPRESS, 250, REWARD_POINTS, 1.0);
	addMultiplier(&cardB, AIRLINES, 4.0);
	addMultiplier(&cardB, STORES, 2.0);
	addMultiplier(&cardB, SERVICES, 1.5);

	cardC = registerCard("Citi", MASTERCARD, 0, CASHBACK, 1.0);
	addMultiplier(&cardC, AIRLINES, 3.0);
	addMultiplier(&cardC, STORES, 2.0);
	addMultiplier(&cardC, SERVICES, 1.0);

	cardD = registerCard("American Express", AMEXPRESS, 0, CASHBACK, 1.0);
	addMultiplier(&cardD, AIRLINES, 3.0);
	addMultiplier(&cardD, STORES, 2.0);
	addMultiplier(&cardD, SERVICES, 2.0);

	cardE = registerCard("Discover", DISCOVER, 0, CASHBACK, 1.0);
	addMultiplier(&cardE, AIRLINES, 4.5);
	addMultiplier(&cardE, STORES, 2.5);
	addMultiplier(&cardE, SERVICES, 1.0);

	logMessage("Test cards initialized.", LOG_INFO);
}