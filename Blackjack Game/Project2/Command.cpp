#include "stdafx.h"
#include "Command.h"
using namespace std;

string Command::getCName() const {
	return command_name;
}

void Command::initialize(vector<User*>* pList, vector<Card*>* cList,
	priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* sPQ) {
	playerList = pList;
	cardDeck = cList;
	scorePQ = sPQ;
}

std::vector<User*>* Command::playerList = NULL;
std::vector<Card*>* Command::cardDeck = NULL;
std::priority_queue<UserScoreInfo, std::vector<UserScoreInfo>, std::less<UserScoreInfo> >* Command::scorePQ = NULL;