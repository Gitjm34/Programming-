#include "stdafx.h"
#include "CommandFactory.h"
#include "CheckLoser.h"
#include "CheckWinner.h"
#include "InitialCardDistribution.h"
#include "PersonalHitRequest.h"
#include "PersonalStopRequest.h"
#include "Replay.h"

using namespace std;

CommandFactory::~CommandFactory() {
	delete this->instance;
	this->instance = NULL;
}

Command * CommandFactory::getCommand(int id, void* inform) const {
	int index = -1;
	switch (id) {
	case CHECK_LOSER:
		return new CheckLoser();
	case CHECK_WINNER:
		if (inform != NULL)
			index = *(int*)inform;
		return new CheckWinner(index);
	case INITIAL_CARD_DISTRIBUTION:
		return new InitialCardDistribution();
	case PERSONAL_HIT_REQUEST:
		if (inform != NULL)
			index = *(int*)inform;
		return new PersonalHitRequest(index, isReplay);
	case PERSONAL_STOP_REQUEST:
		if (inform != NULL)
			index = *(int*)inform;
		return new PersonalStopRequest(index, isReplay);
	case REPLAY:
		if(inform != NULL)
			return new Replay((vector<void*>*)inform);
	default:
		return nullptr;
	}
}

CommandFactory * CommandFactory::getInstace() {
	if (instance == nullptr)
		instance = new CommandFactory;
	return instance;
}

void CommandFactory::setReplay(bool flag) {
	isReplay = flag;
}

CommandFactory* CommandFactory::instance = nullptr;
bool CommandFactory::isReplay = false;