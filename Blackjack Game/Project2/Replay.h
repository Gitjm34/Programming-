#pragma once
#include"stdafx.h"
#include "Command.h"

class Replay : //R
	public Command
{
public:
	Replay(std::vector<void*>* replayLog); //커맨드 이름 R로 초기화 및 replayLog 받아오기

	void execute(); //리플레이 실행
private:
	std::vector<void*> replayLog;
};

