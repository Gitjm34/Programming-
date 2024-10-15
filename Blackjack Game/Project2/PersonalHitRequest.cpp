#include "stdafx.h"
#include "PersonalHitRequest.h"
#include "Card.h"
#include "User.h"

using namespace std;

PersonalHitRequest::PersonalHitRequest(int player, bool isReplay) {
	this->command_name = "PHR";
	this->requestedPlayerIndex = player;
	this->isReplay = isReplay;
}

void PersonalHitRequest::execute() {
	(*this->playerList)[this->requestedPlayerIndex]->addCard(this->cardDeck->back());
	this->cardDeck->pop_back();

	if ((*this->playerList)[this->requestedPlayerIndex]->getID() != AI || isReplay) {
		cout << endl << endl;
		cout << "-----------------------------------------" << endl;
		cout << "<���� ���α׷�>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "���� ����" << endl;
		cout << "-----------------------------------------" << endl;
		cout << (*this->playerList)[this->requestedPlayerIndex]->getName() << "��" << endl << endl;
		cout << "ī�带 �� �� �޾ҽ��ϴ�." << endl;
		cout << "-----------------------------------------" << endl << "\n\n\n\n\n\n\n\n";

		for (u_int j = 0; j < (*this->playerList)[this->requestedPlayerIndex]->getUserCard().size(); j++) {
			Sleep(PRINT_DELAY);
			(*this->playerList)[this->requestedPlayerIndex]->getUserCard()[j]->CardPrint(100*j, 0);
		}

		cout << "���� ī����� ����(����ȭ): " << (*this->playerList)[this->requestedPlayerIndex]->getCardScore() << endl;
		cout << "-----------------------------------------" << endl;
		if ((*this->playerList)[this->requestedPlayerIndex]->getCardScore() > 21) {
			cout << "�й��ϼ̽��ϴ�." << endl;
		}
		cout << " �� �� ���� ȭ������ �Ѿ�ϴ�.";
		for (int i = DELAY; i > 0; i--) {
			cout << "\r";
			cout << i;
			cout << "\t\t\t\t";
			Sleep(1000);
		}
		system("cls");
	}
	
}

void PersonalHitRequest::setIndex(int index) {
	this->requestedPlayerIndex = index;
}

void PersonalHitRequest::setReplay() {
	this->isReplay = true;
}
