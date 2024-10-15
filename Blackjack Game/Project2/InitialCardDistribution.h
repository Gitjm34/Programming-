#pragma once
#include "stdafx.h"
#include "Command.h"

class InitialCardDistribution : //약어: ICD
	public Command
{
public:
	InitialCardDistribution(); //커맨드 이름 ICD로 초기화

	void execute(); //초기 각 플레이어에게 카드2장씩 나누어 주는 기능 실행
};