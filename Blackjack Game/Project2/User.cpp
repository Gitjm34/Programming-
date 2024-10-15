#include "stdafx.h"
#include "User.h"
#include "Card.h"

using namespace std;

User::User(int id, string pw, string name, int score) {
	this->ID = id;
	this->pw = pw;
	this->username = name;
	this->remainScore = score;
}

User::User(const User & u) {
	this->ID = u.ID;
	this->pw = u.pw;
	this->username = u.username;
	this->remainScore = u.remainScore;
}

User::~User() { 
	this->cardsInHand.clear();
}

int User::getID() const {
	return this->ID;
}

string User::getPW() const {
	return this->pw;
}

string User::getName() const {
	return this->username;
}

vector<Card*> User::getUserCard() const {
	return this->cardsInHand;
}

int User::getScore() const {
	return this->remainScore;
}

int User::getCardScore() const {
	int score = 0;
	int aceNum = 0;
	for (Card* card : this->cardsInHand) {
		int cardNum = card->getNum();
		if (cardNum == 12) {
			aceNum++;
			score += 1;
		}
		else if (cardNum >= 9)
			score += 10;
		else
			score += cardNum + 2;
	}
	for (; aceNum > 0; aceNum--) {
		if (score + 10 <= 21)
			score += 10;
		else
			break;
	}
	return score;
}

void User::addCard(Card * card) {
	this->cardsInHand.push_back(card);
}

void User::initCardList() {
	this->cardsInHand.clear();
}

void User::changeScore(int change) {
	this->remainScore += change;
}

void User::printMyInformation() {
	cout << this->username << "\t" << this->remainScore << endl;
}