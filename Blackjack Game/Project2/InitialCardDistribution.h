#pragma once
#include "stdafx.h"
#include "Command.h"

class InitialCardDistribution : //���: ICD
	public Command
{
public:
	InitialCardDistribution(); //Ŀ�ǵ� �̸� ICD�� �ʱ�ȭ

	void execute(); //�ʱ� �� �÷��̾�� ī��2�徿 ������ �ִ� ��� ����
};