#include "stdafx.h"
#include "CheckWinner.h"
#include "User.h"
#include "UserScoreInfo.h"

using namespace std;

CheckWinner::CheckWinner(int betScore) {
	this->command_name = "CW";
	this->betScore = betScore;
}

void CheckWinner::execute() {
	string dummy;
	int scoreSum = 0;
	vector<User*> winner;
	vector<User*> loser;

	while (!this->scorePQ->empty()) {
		int score;

		score = this->scorePQ->top().getScore();
		if(score != -1){
			if (winner.size() == 0) {
				winner.push_back(this->scorePQ->top().getUser());
				this->scorePQ->pop();
			}
			else if (winner[0]->getCardScore() == this->scorePQ->top().getScore()) {
				winner.push_back(this->scorePQ->top().getUser());
				this->scorePQ->pop();
			}
			else {
				loser.push_back(this->scorePQ->top().getUser());
				this->scorePQ->pop();
			}
		}
		else {
			loser.push_back(this->scorePQ->top().getUser());
			this->scorePQ->pop();
		}
	}

	for (User* user : loser) {
		user->changeScore(-betScore);
		scoreSum += betScore;
	}
	if(winner.size())
		scoreSum /= winner.size();
	for (User* user : winner) {
		user->changeScore(scoreSum);
	}

	cout << endl << endl;
	cout << "-----------------------------------------" << endl;
	cout << "<블랙잭 프로그램>" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "최종 결과" << endl;
	cout << "베팅 점수: " << betScore << endl;
	cout << "-----------------------------------------" << endl;
	cout << "승자" << endl;
	cout << "이름\t카드숫자\t총 점수" << endl << endl;

	for (User* user : winner) {
		cout << user->getName() << "\t" << user->getCardScore() << "\t\t" << user->getScore() << " (+" << scoreSum << ")"<< endl;
	}

	cout << "-----------------------------------------" << endl;
	cout << "패자" << endl;
	cout << "이름\t카드숫자\t총 점수" << endl << endl;

	for (User* user : loser) {
		cout << user->getName() << "\t" << user->getCardScore() << "\t\t" << user->getScore() << " (-" << betScore << ")" << endl;
	}

	cout << "-----------------------------------------" << endl;
	cout << "계속하시려면 아무 키나 입력하여 주십시오." << endl;
	cin >> dummy;
	system("cls");
}