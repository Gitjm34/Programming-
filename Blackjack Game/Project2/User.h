#pragma once
#include "stdafx.h"

class Card;

class User
{
public:
	User(int id, std::string pw, std::string name, int score); //각 인자 초기화
	User(const User &u); //복사 생성자
	~User(); //동적할당된 변수 delete

	int getID() const; //ID 반환
	std::string getPW() const; //pw 반환
	std::string getName() const; //username 반환
	std::vector<Card*> getUserCard() const; //cardsInHand 반환
	int getScore() const; //reamainScore 반환
	int getCardScore() const; //CardInHand의 점수 계산후 반환

	void addCard(Card* card); //cardsInHand에 카드 추가
	void initCardList(); //cardsInHand 초기화
	void changeScore(int change); //change만큼 remainScore변화

	void printMyInformation(); //username과 remainScore 출력

private:
	int ID;
	std::string pw;
	std::string username;
	int remainScore;
	std::vector<Card*> cardsInHand;
};

