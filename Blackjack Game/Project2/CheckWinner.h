#pragma once
#include "stdafx.h"
#include "Command.h"

class CheckWinner : //���: CW
	public Command
{
public:
	CheckWinner(int betScore); //Ŀ�ǵ� �̸� CW�� �ʱ�ȭ

	void execute(); //������ ���� �� ���� ī�������� ���� score���, ���� ���� �� �й�
private:
	int betScore;
};