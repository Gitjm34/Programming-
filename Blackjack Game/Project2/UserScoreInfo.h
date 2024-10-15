#pragma once
#include"stdafx.h"

class User;

class UserScoreInfo
{
public:
	UserScoreInfo(User* user); //user변수 초기화

	void calculateScore(); //user 의 카드정보를 받아 점수로 환산 후 score에 저장(21을 넘을 경우 -1로 저장)
	bool operator<(const UserScoreInfo& b) const; //priorityQueue를 사용하기 위한 연산자 오버로딩(score 비교)
	int getScore() const; //score 반환
	User* getUser() const; //user 반환

private:
	User* user;
	int score;
};

