#ifndef CARDS_H
#define CARD_H

#include <Windows.h>

enum Network {
    VISA,
    MASTERCARD,
    AMEXPRESS,
	DISCOVER
};

enum Reward {
	CASHBACK,
	REWARD_POINTS,
	MILES
};

enum MerchantCategory {
	AGRICULTURE,
	CONSTRUCTION,
	AIRLINES,
	CAR_RENTAL,
	HOTEL,
	UTILITIES,
	STORES,
	SERVICES,
	ORGANIZATIONS,
	GOVERNMENT
};

typedef struct {
	enum MerchantCategory category;
	double multiplier;
} Multiplier;

typedef struct {
	GUID guid;

    char* issuer;
	enum Network network;
	int annualFee;

	enum Reward reward;
	double rate;

	Multiplier multipliers[10];
} Card;

Card registerCard(char* issuer, enum Network network, int annualFee, enum Reward reward, double rate);

void addMultiplier(Card* card, enum MerchantCategory category, double multiplier);

Card* testGetCard(int id);
void initTestCards();

double calculateReward(Card* card, enum MerchantCategory category, double amount);

LPCWSTR getGUIDAsLPCWSTR(GUID guid);
LPCWSTR getBaseInfo(Card card);
LPCWSTR getMultiplierInfo(Card card);

#endif
