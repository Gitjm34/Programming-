#include "stdafx.h"
#include "UserScoreInfo.h"
#include "User.h"
#include "Card.h"

using namespace std;

UserScoreInfo::UserScoreInfo(User * user) {
	this->user = user;
	this->calculateScore();
}

void UserScoreInfo::calculateScore() {
	this->score = 0;
	int aceNum = 0;
	for (Card* card : this->user->getUserCard()) {
		int cardNum = card->getNum();
		if (cardNum == 12) {
			aceNum++;
			this->score += 1;
		}
		else if (cardNum >= 9)
			this->score += 10;
		else
			this->score += cardNum + 2;
	}
	for (; aceNum > 0; aceNum--) {
		if (this->score + 10 <= 21)
			this->score += 10;
		else
			break;
	}
	if (this->score > 21)
		this->score = -1;
}

bool UserScoreInfo::operator<(const UserScoreInfo& b) const {
	if (this->score < b.score)
		return true;
	else
		return false;
}

int UserScoreInfo::getScore() const {
	return this->score;
}

User* UserScoreInfo::getUser() const {
	return this->user;
}