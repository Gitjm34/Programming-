#pragma once
#include"stdafx.h"

class CardGraphic;

class Card
{
public:
	Card(int number, int suit); //ī�� ������. ���ڷ� ������ ��ȣ�� �޾ƿ�
	Card(const Card &c); //ī�� ���� ������

	int getSuit() const; //ī�� ���� ��ȯ
	int getNum() const; //ī�� ��ȣ ��ȯ

	void CardPrint(int x, int y); //x, y ��ǥ�� �ش�ī�� ���
private:
	int number;
	int suit;
	static CardGraphic cg;
};


