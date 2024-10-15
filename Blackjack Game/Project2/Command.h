#pragma once
#include"stdafx.h"

class User;
class Card;
class UserScoreInfo;

class Command
{
public:
	virtual void execute() = 0; //�� Ŀ�ǵ庰 ����� �����ϱ� ���� �����Լ�

	std::string getCName() const; //�� Ŀ�ǵ庰 �̸��� �޾ƿ��� ���� �Լ�

	static void Command::initialize(std::vector<User*>* pList, std::vector<Card*>* cList,
		std::priority_queue<UserScoreInfo, std::vector<UserScoreInfo>, std::less<UserScoreInfo>>* sPQ); //Ŀ�ǵ� ���� ������ �ʱ�ȭ

protected:
	std::string command_name;
	static std::vector<User*> *playerList;
	static std::vector<Card*> *cardDeck;
	static std::priority_queue<UserScoreInfo, std::vector<UserScoreInfo>, std::less<UserScoreInfo> > *scorePQ;
};

