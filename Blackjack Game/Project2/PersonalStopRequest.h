#pragma once
#include "stdafx.h"
#include "Command.h"
#include "User.h"

class PersonalStopRequest : 
	public Command {
public:
	PersonalStopRequest(int player, bool isReplay = false); //커맨드 이름 PSR로 초기화 및 playerIndex 설정
	
	void execute(); //해당 index플레이어를 playerList에서 제거
	void setIndex(int index); //playerIndex 설정
	void setReplay();

private:
	int requestedPlayerIndex;
	bool isReplay;
};
