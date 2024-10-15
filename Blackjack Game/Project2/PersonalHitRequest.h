#pragma once
#include "stdafx.h"
#include "Command.h"
#include "User.h"

class PersonalHitRequest : // PHR
	public Command
{
public:
	PersonalHitRequest(int player, bool isReplay = false); //Ŀ�ǵ� �̸� PHR�� �ʱ�ȭ �� playerIndex ����
	
	void execute(); //index�÷��̾�� ī�� 1�� ����
	void setIndex(int index); //index ����
	void setReplay();

private:
	int requestedPlayerIndex;
	bool isReplay;
};