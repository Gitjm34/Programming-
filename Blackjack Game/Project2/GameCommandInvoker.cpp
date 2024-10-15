#include "stdafx.h"
#include "GameCommandInvoker.h"
#include "Command.h"

using namespace std;


GameCommandInvoker::GameCommandInvoker() {
	this->curCommand = nullptr;
}

GameCommandInvoker::~GameCommandInvoker() {
	resetLog();
	if (curCommand != nullptr) {
		delete this->curCommand;
	}
}

void GameCommandInvoker::executeCommand() {
	if (curCommand != nullptr) {
		this->replayLog.push_back(curCommand);
		this->curCommand->execute();
	}
	else
		cout << "커맨드에러! 할당안됨.";
}

vector<Command*> GameCommandInvoker::getReplayLog() const {
		return this->replayLog;
}

void GameCommandInvoker::resetLog() {
	for (Command* com : replayLog) {
		if (com != nullptr) {
			delete com;
			com = nullptr;	
		}
	}
	curCommand = nullptr;
	replayLog.clear();
}

void GameCommandInvoker::getCommand(Command * newCom) {
	this->curCommand = newCom;
}