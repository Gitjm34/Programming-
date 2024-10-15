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
		cout << "<블랙잭 프로그램>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "블랙잭 게임" << endl;
		cout << "-----------------------------------------" << endl;
		cout << (*this->playerList)[this->requestedPlayerIndex]->getName() << "님" << endl << endl;
		cout << "카드를 그만 받습니다." << endl;
		cout << "-----------------------------------------" << endl << "\n\n\n\n\n\n\n\n";

		for (u_int j = 0; j < (*this->playerList)[this->requestedPlayerIndex]->getUserCard().size(); j++) {
			Sleep(PRINT_DELAY);
			(*this->playerList)[this->requestedPlayerIndex]->getUserCard()[j]->CardPrint(100 * j, 0);
		}

		cout << "현재 카드숫자 총합(최적화): " << (*this->playerList)[this->requestedPlayerIndex]->getCardScore() << endl;
		cout << "-----------------------------------------" << endl;
		cout << " 초 뒤 다음 화면으로 넘어갑니다.";
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
