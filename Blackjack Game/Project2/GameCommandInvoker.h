#pragma once
#include "stdafx.h"

class Command;

class GameCommandInvoker
{
public:
	GameCommandInvoker();
	~GameCommandInvoker(); //동적할당된 커맨드들 delete

	void executeCommand(); //curCommand에 들어있는 커맨드 실행

	std::vector<Command*> getReplayLog() const; //가지고 있는 replayLog 반환
	void  getCommand(Command* newCom); //새로운 커맨드를 받아옴

	void resetLog(); //replayLog 리셋

private:
	Command* curCommand;
	std::vector<Command*> replayLog;
};

