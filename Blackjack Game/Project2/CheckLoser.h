#pragma once
#include"stdafx.h"
#include "Command.h"

class CheckLoser : //약어: CL
	public Command
{
public:
	CheckLoser(); //커맨드 이름 CL로 초기화

	void execute(); //커맨드 실행. 패배한 유저를 찾아 playerList에서 제거
};