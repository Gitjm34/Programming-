#pragma once
#include "stdafx.h"
#include "Command.h"

class CheckWinner : //약어: CW
	public Command
{
public:
	CheckWinner(int betScore); //커맨드 이름 CW로 초기화

	void execute(); //게임이 끝난 후 유저 카드점수를 토대로 score계산, 순위 결정 및 분배
private:
	int betScore;
};