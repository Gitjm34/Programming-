#pragma once
#include "stdafx.h"
#include "Command.h"
#include "User.h"

class PersonalHitRequest : // PHR
	public Command
{
public:
	PersonalHitRequest(int player, bool isReplay = false); //커맨드 이름 PHR로 초기화 및 playerIndex 설정
	
	void execute(); //index플레이어에게 카드 1장 지급
	void setIndex(int index); //index 설정
	void setReplay();

private:
	int requestedPlayerIndex;
	bool isReplay;
};