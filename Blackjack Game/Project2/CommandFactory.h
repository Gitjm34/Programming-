#pragma once
#include "stdafx.h"

class Command;

class CommandFactory {
private:
	CommandFactory() {} //�̱��� ������ ���Ͽ� private�� ����
	
public:
	~CommandFactory(); //instance �޸� ��ȯ�� ���� �Ҹ���

	Command* getCommand(int id, void* inform = NULL) const; //id�� �´� Ŀ�ǵ带 �����ϰ� ��ȯ��. �ʿ��� ��� inform�� ������ ���ڷ� ����
	static CommandFactory* getInstace(); //�̱��������̹Ƿ� CommandFactory�� �ν��Ͻ��� �ޱ� ���� static�Լ�
	static void setReplay(bool flag);

private:
	static CommandFactory* instance;//
	static bool isReplay;
};
