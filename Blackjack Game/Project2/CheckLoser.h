#pragma once
#include"stdafx.h"
#include "Command.h"

class CheckLoser : //���: CL
	public Command
{
public:
	CheckLoser(); //Ŀ�ǵ� �̸� CL�� �ʱ�ȭ

	void execute(); //Ŀ�ǵ� ����. �й��� ������ ã�� playerList���� ����
};