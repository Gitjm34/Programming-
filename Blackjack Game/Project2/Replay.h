#pragma once
#include"stdafx.h"
#include "Command.h"

class Replay : //R
	public Command
{
public:
	Replay(std::vector<void*>* replayLog); //Ŀ�ǵ� �̸� R�� �ʱ�ȭ �� replayLog �޾ƿ���

	void execute(); //���÷��� ����
private:
	std::vector<void*> replayLog;
};

