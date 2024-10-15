#include "stdafx.h"
#include "Replay.h"
#include "User.h"
#include "UserScoreInfo.h"
#include "PersonalHitRequest.h"
#include "PersonalStopRequest.h"
#include "InitialCardDistribution.h"
#include "CheckLoser.h"
#include "CheckWinner.h"
#include "CommandFactory.h"

using namespace std;

Replay::Replay(vector<void*>* replayLog) {
	this->replayLog = *replayLog;
}

void Replay::execute() {//리플레이 실행하기
	vector<User*> alivePlayerList, userListTemp;
	vector<Card*> deck = CARD_LIST replayLog[DECK];
	vector<Command*> commandList = COMMAND_LIST replayLog[COMMAND];

	for (User* user : PLAYER_LIST replayLog[PLAYER])
		alivePlayerList.push_back(new User(*user));
	userListTemp = alivePlayerList;

	priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>> scorePQ;
	int comIndex = 0;

	Command::initialize(&alivePlayerList, &deck, &scorePQ);

	commandList[comIndex++]->execute();

	while (alivePlayerList.size()) {
		for (unsigned int i = 0; i < alivePlayerList.size(); i++) {
			if (commandList[comIndex]->getCName() == "PHR") {
				unsigned int beforeNum = alivePlayerList.size();
				dynamic_cast<PersonalHitRequest*>(commandList[comIndex])->setIndex(i);
				dynamic_cast<PersonalHitRequest*>(commandList[comIndex])->setReplay();

				commandList[comIndex++]->execute();
				commandList[comIndex++]->execute();

				if (beforeNum > alivePlayerList.size())
					--i;
			}
			else {
				dynamic_cast<PersonalStopRequest*>(commandList[comIndex])->setIndex(i);
				dynamic_cast<PersonalStopRequest*>(commandList[comIndex])->setReplay();
				commandList[comIndex++]->execute();
				--i;
			}
		}
	}

	for (User* user : userListTemp)
		scorePQ.push(UserScoreInfo(user));

	commandList[comIndex]->execute();

	for (User* user : alivePlayerList) {
		delete user;
	}
}  