#include"stdafx.h"
#include"InitialCardDistribution.h"
#include "User.h"

using namespace std;

InitialCardDistribution::InitialCardDistribution() {
	this->command_name = "ICD";
}

void InitialCardDistribution::execute() {
	for (User* user : (*this->playerList)) {
		for (int i = 0; i < INIT_CARD_NUM; i++) {
			user->addCard(this->cardDeck->back());
			this->cardDeck->pop_back();
		}
	}
}