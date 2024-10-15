#pragma once
#include"stdafx.h"

class User;
class Card;
class UserScoreInfo;

class Command
{
public:
	virtual void execute() = 0; //각 커맨드별 기능을 수행하기 위한 가상함수

	std::string getCName() const; //각 커맨드별 이름을 받아오기 위한 함수

	static void Command::initialize(std::vector<User*>* pList, std::vector<Card*>* cList,
		std::priority_queue<UserScoreInfo, std::vector<UserScoreInfo>, std::less<UserScoreInfo>>* sPQ); //커맨드 공유 변수값 초기화

protected:
	std::string command_name;
	static std::vector<User*> *playerList;
	static std::vector<Card*> *cardDeck;
	static std::priority_queue<UserScoreInfo, std::vector<UserScoreInfo>, std::less<UserScoreInfo> > *scorePQ;
};

