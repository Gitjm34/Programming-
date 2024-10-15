#include "stdafx.h"
#include "CheckLoser.h"
#include "User.h"
#include "UserScoreInfo.h"

using namespace std;

CheckLoser::CheckLoser() {
	this->command_name = "CL";
}

void CheckLoser::execute() {
	for (u_int i = 0; i < this->playerList->size(); i++) {
		if ((*this->playerList)[i]->getCardScore() > 21) {
			(*this->playerList).erase((*this->playerList).begin() + i);
			i--;
		}
	}
}