#pragma once
#include "stdafx.h"

class Card;

class User
{
public:
	User(int id, std::string pw, std::string name, int score); //�� ���� �ʱ�ȭ
	User(const User &u); //���� ������
	~User(); //�����Ҵ�� ���� delete

	int getID() const; //ID ��ȯ
	std::string getPW() const; //pw ��ȯ
	std::string getName() const; //username ��ȯ
	std::vector<Card*> getUserCard() const; //cardsInHand ��ȯ
	int getScore() const; //reamainScore ��ȯ
	int getCardScore() const; //CardInHand�� ���� ����� ��ȯ

	void addCard(Card* card); //cardsInHand�� ī�� �߰�
	void initCardList(); //cardsInHand �ʱ�ȭ
	void changeScore(int change); //change��ŭ remainScore��ȭ

	void printMyInformation(); //username�� remainScore ���

private:
	int ID;
	std::string pw;
	std::string username;
	int remainScore;
	std::vector<Card*> cardsInHand;
};

