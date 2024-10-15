#include "stdafx.h"
#include "Card.h"
#include "CardGraphic.h"

using namespace std;

Card::Card(int number, int suit) {
	this->number = number;
	this->suit = suit;
}

Card::Card(const Card & c) {
	this->number = c.number;
	this->suit = c.suit;
}

int Card::getSuit() const {
	return this->suit;
}

int Card::getNum() const {
	return this->number;
}

void Card::CardPrint(int x, int y) {
	this->cg.print(x, y, this);
}

CardGraphic Card::cg("cardImage.png");