#include "stdafx.h"
#include "PersonalStopRequest.h"
#include "Card.h"

using namespace std;

PersonalStopRequest::PersonalStopRequest(int player, bool isReplay) {
	this->command_name = "PSR";
	this->requestedPlayerIndex = player;
	this->isReplay = isReplay;
}

void PersonalStopRequest::execute() {
	if ((*this->playerList)[this->requestedPlayerIndex]->getID() != AI || isReplay) {
		cout << endl << endl;
		cout << "-----------------------------------------" << endl;
		cout << "<���� ���α׷�>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "���� ����" << endl;
		cout << "-----------------------------------------" << endl;
		cout << (*this->playerList)[this->requestedPlayerIndex]->getName() << "��" << endl << endl;
		cout << "ī�带 �׸� �޽��ϴ�." << endl;
		cout << "-----------------------------------------" << endl << "\n\n\n\n\n\n\n\n";

		for (u_int j = 0; j < (*this->playerList)[this->requestedPlayerIndex]->getUserCard().size(); j++) {
			Sleep(PRINT_DELAY);
			(*this->playerList)[this->requestedPlayerIndex]->getUserCard()[j]->CardPrint(100 * j, 0);
		}

		cout << "���� ī����� ����(����ȭ): " << (*this->playerList)[this->requestedPlayerIndex]->getCardScore() << endl;
		cout << "-----------------------------------------" << endl;
		cout << " �� �� ���� ȭ������ �Ѿ�ϴ�.";
		for (int i = DELAY; i > 0; i--) {
			cout << "\r";
			cout << i;
			cout << "\t\t\t\t";
			Sleep(1000);
		}
		system("cls");
	}

	this->playerList->erase(this->playerList->begin() + this->requestedPlayerIndex);
}

void PersonalStopRequest::setIndex(int index) {
	this->requestedPlayerIndex = index;
}

void PersonalStopRequest::setReplay() {
	this->isReplay = true;
}
