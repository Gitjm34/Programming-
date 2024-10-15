#pragma once
#include"stdafx.h"

class User;

class UserScoreInfo
{
public:
	UserScoreInfo(User* user); //user���� �ʱ�ȭ

	void calculateScore(); //user �� ī�������� �޾� ������ ȯ�� �� score�� ����(21�� ���� ��� -1�� ����)
	bool operator<(const UserScoreInfo& b) const; //priorityQueue�� ����ϱ� ���� ������ �����ε�(score ��)
	int getScore() const; //score ��ȯ
	User* getUser() const; //user ��ȯ

private:
	User* user;
	int score;
};

