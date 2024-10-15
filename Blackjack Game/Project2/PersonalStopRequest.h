#pragma once
#include "stdafx.h"
#include "Command.h"
#include "User.h"

class PersonalStopRequest : 
	public Command {
public:
	PersonalStopRequest(int player, bool isReplay = false); //Ŀ�ǵ� �̸� PSR�� �ʱ�ȭ �� playerIndex ����
	
	void execute(); //�ش� index�÷��̾ playerList���� ����
	void setIndex(int index); //playerIndex ����
	void setReplay();

private:
	int requestedPlayerIndex;
	bool isReplay;
};
