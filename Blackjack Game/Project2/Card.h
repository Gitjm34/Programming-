#pragma once
#include"stdafx.h"

class CardGraphic;

class Card
{
public:
	Card(int number, int suit); //카드 생성자. 인자로 종류와 번호를 받아옴
	Card(const Card &c); //카드 복사 생성자

	int getSuit() const; //카드 종류 반환
	int getNum() const; //카드 번호 반환

	void CardPrint(int x, int y); //x, y 좌표에 해당카드 출력
private:
	int number;
	int suit;
	static CardGraphic cg;
};


