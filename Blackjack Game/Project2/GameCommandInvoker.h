#pragma once
#include "stdafx.h"

class Command;

class GameCommandInvoker
{
public:
	GameCommandInvoker();
	~GameCommandInvoker(); //�����Ҵ�� Ŀ�ǵ�� delete

	void executeCommand(); //curCommand�� ����ִ� Ŀ�ǵ� ����

	std::vector<Command*> getReplayLog() const; //������ �ִ� replayLog ��ȯ
	void  getCommand(Command* newCom); //���ο� Ŀ�ǵ带 �޾ƿ�

	void resetLog(); //replayLog ����

private:
	Command* curCommand;
	std::vector<Command*> replayLog;
};

