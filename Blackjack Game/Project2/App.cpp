#include "stdafx.h"
#include "App.h"
#include "CommandFactory.h"
#include "GameCommandInvoker.h"
#include "CheckLoser.h"
#include "CheckWinner.h"
#include "InitialCardDistribution.h"
#include "PersonalHitRequest.h"
#include "PersonalStopRequest.h"
#include "Replay.h"
#include "Card.h"
#include "User.h"
#include "UserScoreInfo.h"

using namespace std;

App::App() {
	readUserFile();
	readReplayFile();
	this->gci = new GameCommandInvoker;
	
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 12; j++) {
			this->mainDeck.push_back(new Card(j, i));
		}
	}
}

App::~App() {
	saveUserFile();
	saveReplayFile();

	delete gci;
	for (User* user : this->userList)
		delete user;
	for (Card* card : this->deck)
		delete card;
	for (u_int i = 0; i < playerListForReplay.size();i++) {
		for (Command* com : this->replayLog[i])
			delete com;
		for (User* user : this->playerListForReplay[i])
			delete user;
		for (Card* card : this->shuffledDeckForReplay[i])
			delete card;
	}
} 

void App::run() {
	int command;

	while (1) {
		cout << endl << endl;
		cout << "-----------------------------------------" << endl;
		cout << "<���� ���α׷�>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "����� ������ �ݰ����ϴ�!" << endl;
		cout << "-----------------------------------------" << endl;

		if (this->playerList.size() == 0) {
			cout << "1. �α���" << endl;
			cout << "2. ȸ������" << endl;
		}
		else {
			cout << "�ִ� �÷��̾� ��: 6" << endl;
			cout << "���� �÷��̾� ��: " << playerList.size() << endl;
			cout << "-----------------------------------------" << endl;
			cout << "1. �α���" << endl;
			cout << "2. ȸ������" << endl;
			cout << "3. ���� ����" << endl;
			cout << "4. ���÷��� ����" << endl;
			cout << "5. ���� ���� ����" << endl;
			cout << "6. �α׾ƿ�" << endl;
		}

		cout << "0. ���α׷� ����" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "-> ";

		cin >> command;
		system("cls");

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "�߸��� �Է��Դϴ�.";
			continue;
		}

		switch (command) {
		case 0:
			cout << "�����մϴ�!" << endl;
			return;
		case 1:
			this->login();
			break;
		case 2:
			this->newAccount();
			break;
		case 3:
			if (this->playerList.size()) {
				this->playGame();
				break;
			}
		case 4:
			if (this->playerList.size()) {
				this->showReplay();
				break;
			}
		case 5:
			if (this->playerList.size()) {
				this->showUserInfo();
				break;
			}
		case 6:
			if (this->playerList.size()) {
				this->logout();
				break;
			}
		default:
			cout << "�߸��� �Է��Դϴ�.";
		}
	}
}

void App::login() {
	int id;
	string pw;

	if (this->playerList.size() < 6) {
		while (1) {
			cout << endl << endl;
			cout << "-----------------------------------------" << endl;
			cout << "<���� ���α׷�>" << endl;
			cout << "-----------------------------------------" << endl;
			cout << "�α���" << endl;
			cout << "-----------------------------------------" << endl;
			cout << "���̵� �Է��Ͽ� �ֽʽÿ�" << endl;
			cout << "id -> ";
			cin >> id;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(100, '\n');
				system("cls");
				cout << "�߸��� �Է��Դϴ�.";
				continue;
			}

			cout << "-----------------------------------------" << endl;
			cout << "��й�ȣ�� �Է��Ͽ� �ֽʽÿ�." << endl;
			cout << "Password -> ";
			cin >> pw;
			system("cls");

			for (User* user : this->userList) {
				if (user->getID() == id && user->getPW() == pw) {
					for (User* check_user : this->playerList) {
						if (user == check_user) {
							cout << "�̹� �α��ε� �����Դϴ�.";
							return;
						}
					}
					this->playerList.push_back(user);
					return;
				}
			}

			cout << "ID Ȥ�� Password�� �߸��Ǿ����ϴ�.";
			return;
		}
	}
	else
		cout << "�÷��̾� ���� 6���� ���� �� �����ϴ�.";
}

void App::logout() {
	u_int command;

	while (1) {
		cout << endl << endl;
		cout << "-----------------------------------------" << endl;
		cout << "<���� ���α׷�>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "�α׾ƿ�" << endl;
		cout << "-----------------------------------------" << endl;

		int i = 1;
		for (User* user : this->playerList) {
			cout << i << ". \"" << user->getName() << "\"��" << endl;
			++i;
		}
		cout << "0. �ڷΰ���" << endl;

		cout << "-----------------------------------------" << endl;
		cout << "-> ";
		cin >> command;
		system("cls");

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "�߸��� �Է��Դϴ�.";
		}
		else if (command == 0) {
			return;
		}
		else if (command > 0 && command <= this->playerList.size()) {
			this->playerList.erase(this->playerList.begin() + command - 1);
		}
		else
			cout << "�߸��� �Է��Դϴ�.";
	}
}

void App::newAccount() {
	int id;
	bool duplication;
	string pw;
	string name;

	while (1) {
		duplication = false;
		cout << endl << endl;
		cout << "-----------------------------------------" << endl;
		cout << "<���� ���α׷�>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "ȸ������" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "������ id: ";
		cin >> id;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			system("cls");
			cout << "�߸��� �Է��Դϴ�.";
			continue;
		}
		for (User* user : userList) {
			if (user->getID() == id) {
				system("cls");
				cout << "�ߺ��Ǵ� ID�� �����մϴ�.";
				duplication = true;
			}
		}
		if (duplication)
			continue;
		
		cout << "������ pw(��й�ȣ): ";
		cin >> pw;

		cout << "����ڴ��� �̸�: ";
		cin >> name;

		this->userList.push_back(new User(id, pw, name, INIT_SCORE));
		system("cls");

		cout << "���������� ���ԵǾ����ϴ�.";
		return;
	}
}

void App::readUserFile() {
	ifstream file;
	int id;
	int score;
	string pw;
	string name;

	file.open(".\\data\\user.txt");

	if (!file.is_open()) {
		cout << "user.txt.������ �дµ��� �����߽��ϴ�." << endl;
		exit(0);
	}

	while (file >> id) {
		file >> pw >> name >> score;

		this->userList.push_back(new User(id, pw, name, score));
	}
	file.close();
}

void App::saveUserFile() {
	ofstream file;
	
	file.open(".\\data\\user.txt");

	for (User* user : this->userList) {
		file << user->getID() << '\t' << user->getPW() << '\t' << user->getName() << '\t' << user->getScore() << endl;
	}

	file.close();
}

void App::readReplayFile() {
	ifstream file;
	string list;
	string temp;
	vector<Card*> saveDeck;
	vector<User*> saveUserList;
	vector<Command*> saveCom;
	int offset;
	int betScore;

	file.open(".\\data\\replay.txt");

	if (!file.is_open()) {
		cout << "replay.txt ������ �дµ� �����߽��ϴ�." << endl;
		exit(0);
	}

	while (file >> list) {
		while (!list.empty()) {
			int id;
			int score;
			string name;

			offset = list.find("/");
			temp = list.substr(0, offset);
			list = list.substr(offset + 1);

			id = stoi(temp);

			offset = list.find("/");
			temp = list.substr(0, offset);
			list = list.substr(offset + 1);

			score = stoi(temp);

			offset = list.find(",");
			temp = list.substr(0, offset);
			list = list.substr(offset + 1);

			name = temp;

			for (User* user : this->userList) {
				if (id == AI) {
					saveUserList.push_back(new User(id, "", name, INIT_SCORE));
					break;
				}
				else if (user->getID() == id) {
					saveUserList.push_back(new User(id, user->getPW(), user->getName(), score));
					break;
				}
			}
		}
		this->playerListForReplay.push_back(saveUserList);

		file >> betScore;
		this->betScoreForReplay.push_back(betScore);

		file >> list;
		while (!list.empty()) {
			int suit;
			int num;

			offset = list.find("/");
			temp = list.substr(0, offset);
			list = list.substr(offset + 1);

			suit = stoi(temp);

			offset = list.find(",");
			temp = list.substr(0, offset);
			list = list.substr(offset + 1);

			num = stoi(temp);

			saveDeck.push_back((new Card(num, suit)));
		}
		this->shuffledDeckForReplay.push_back(saveDeck);

		file >> list;
		while (!list.empty()) {
			string command;
			int i = 0;

			offset = list.find(",");
			command = list.substr(0, offset);
			list = list.substr(offset + 1);
			
			if (command == "CL")
				saveCom.push_back(CommandFactory::getInstace()->getCommand(CHECK_LOSER));
			else if (command == "CW")
				saveCom.push_back(CommandFactory::getInstace()->getCommand(CHECK_WINNER, &betScore));
			else if (command == "ICD")
				saveCom.push_back(CommandFactory::getInstace()->getCommand(INITIAL_CARD_DISTRIBUTION));
			else if (command == "PHR") 
				saveCom.push_back(CommandFactory::getInstace()->getCommand(PERSONAL_HIT_REQUEST));
			else if (command == "R")
				saveCom.push_back(CommandFactory::getInstace()->getCommand(REPLAY));
			else if (command == "PSR") 
				saveCom.push_back(CommandFactory::getInstace()->getCommand(PERSONAL_STOP_REQUEST));
		
		}
		this->replayLog.push_back(saveCom);

		saveUserList.clear();
		saveCom.clear();
		saveDeck.clear();
	}
	file.close();
}

void App::saveReplayFile() {
	ofstream file;
	stringstream sStream;
	
	file.open(".\\data\\replay.txt");

	for(u_int i=0;i<this->playerListForReplay.size();i++) {
		for (User* user : playerListForReplay[i]) {
			sStream << user->getID() << '/' << user->getScore() << '/' << user->getName() << ',';
		}
		sStream << '\t';

		sStream << betScoreForReplay[i];
		sStream << '\t';

		for (Card* card : shuffledDeckForReplay[i]) {
			sStream << card->getSuit() << '/' << card->getNum() << ',';
		}
		sStream << '\t';

		for (Command* com : replayLog[i]) {
			sStream << com->getCName() << ',';
		}
		file << sStream.str() << endl;

		sStream.str("");
	}
	file.close();
}

void App::playGame() {

   /*******************************************************************************************************************************************************
   /////////////////////////////////////////////////////////////////////�ʱ⼼��//////////////////////////////////////////////////////////////////////////
   *******************************************************************************************************************************************************/
	//�÷��̾��������, ī�弯��, ������������, AI����
	//���� ���÷��� ���Ϳ� �ش� ������ push

	int betScore = 0;
	vector<UserScoreInfo> score;

	if (this->playerList.size() == 1) {
		this->AISetting();
		if (this->playerList.size() == 1) //AI�� �߰����� �ʾ��� ���. ��, "��������"�� ������ ���
			return;
	}
	else {
		betScore = this->bettingScore(); //�������� ����
		if (!betScore) {
			return;
		}
	}

	alivePlayerList = playerList;
	this->settingOrder(); //���� ����(�α��μ� or ����)
	this->suffleDeck(); //ī�弯��

	vector<Card*> saveDeck;
	vector<User*> savePlayerList;

	for (Card* card : deck)
		saveDeck.push_back(new Card(*card));
	for (User* user : alivePlayerList)
		savePlayerList.push_back(new User(*user));

	this->shuffledDeckForReplay.push_back(saveDeck); //���÷��� ī�嵦 �߰�
	this->playerListForReplay.push_back(savePlayerList); //���÷��� �÷��̾��Ʈ �߰�
	
	this->betScoreForReplay.push_back(betScore);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*******************************************************************************************************************************************************
	/////////////////////////////////////////////////////////////////////���ӽ���//////////////////////////////////////////////////////////////////////////
	*******************************************************************************************************************************************************/
	//Ŀ�ǵ� �ʱ�ȭ
	//���� InitialCardDistribution Ŀ�ǵ� �ǽ� �� ���� ����.
	//���������� CheckWinnerĿ�ǵ� ���� �� �� ����Ʈ �ʱ�ȭ �� Ŀ�ǵ帮��Ʈ ���÷��̺��Ϳ� �߰�.

	Command::initialize(&this->alivePlayerList, &this->deck, &this->scorePQ);

	this->gci->getCommand(CommandFactory::getInstace()->getCommand(INITIAL_CARD_DISTRIBUTION));
	this->gci->executeCommand();
	
	this->gameProcedure(); //���� �����Լ�. ���������� Ŀ�ǵ��������� ����.

	for (User* user : playerList)
		this->scorePQ.push(UserScoreInfo(user));

	this->gci->getCommand(CommandFactory::getInstace()->getCommand(CHECK_WINNER, &betScore));
	this->gci->executeCommand();

	for (u_int i = 0; i < playerList.size();i++) {
		playerList[i]->initCardList();
		if (playerList[i]->getID() == AI) {
			playerList.erase(playerList.begin() + i);
			--i;
		}
	}

	this->saveCommand(betScore);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void App::showReplay() { //�޴� ����� ���⼭ �ϰ� ���� Ŀ�ǵ� ���͸� ���÷��̷� �ѱ� �� ��.
	vector<void*> replayData;
	int command;

	while (1) {
		cout << endl << endl;
		cout << "-----------------------------------------" << endl;
		cout << "<���� ���α׷�>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "���÷��� ����" << endl;
		cout << "-----------------------------------------" << endl << endl;
		
		for (u_int i = 0; i < playerListForReplay.size(); i++) {
			cout << i + 1 << ".";
			for (User* user : playerListForReplay[i]) {
				cout << " [" << user->getName() << "]";
			}
			cout << endl << "�������� " <<  this->betScoreForReplay[i] << "���� ����" << endl << endl;
		}

		cout << "0. �ڷ� ����" << endl << endl;
		cout << "-----------------------------------------" << endl;
		cout << "������ ���÷���-> ";
		

		cin >> command;
		system("cls");

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "�߸��� �Է��Դϴ�.";
		}
		else if (command == 0) {
			return;
		}
		else if (command > 0 && command <= playerListForReplay.size()) {
			replayData.push_back(&this->playerListForReplay[command-1]);
			replayData.push_back(&this->shuffledDeckForReplay[command-1]);
			replayData.push_back(&this->replayLog[command-1]);

			this->gci->getCommand(CommandFactory::getInstace()->getCommand(REPLAY, &replayData));
			gci->executeCommand();
			return;
		}
		else {
			cout << "�߸��� �Է��Դϴ�.";
		}
	}
	gci->resetLog();
}

void App::showUserInfo() {
	string dummy;

	cout << endl << endl;
	cout << "-----------------------------------------" << endl;
	cout << "<���� ���α׷�>" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "���� ���� ����" << endl;
	cout << "-----------------------------------------" << endl << endl;
	cout << "�̸�\t���� ����" << endl << endl;

	for (User* user : playerList) {
		user->printMyInformation();
	}

	cout << "-----------------------------------------" << endl;
	cout << "��� �Ͻ÷��� �ƹ� Ű�� �Է��Ͽ� �ֽʽÿ�. ";
	cin >> dummy;

	system("cls");
}

void App::suffleDeck() {
	srand((u_int)time(NULL));

	if (this->deck.size()) {
		this->deck.clear();
	}

	for (int i = MAX_CARD; i > 0; i--) {
		int j = rand() % (i + 1);
		Card* temp;

		temp = mainDeck[i];
		mainDeck[i] = mainDeck[j];
		mainDeck[j] = temp;
	}

	for (Card* card : mainDeck) {
		this->deck.push_back(card);
	}
}

void App::saveCommand(int betScore) {
	vector<Command*> saveCom;

	for (Command* com : this->gci->getReplayLog()) {
		string command = com->getCName();
		if (command == "CL")
			saveCom.push_back(CommandFactory::getInstace()->getCommand(CHECK_LOSER));
		else if (command == "CW")
			saveCom.push_back(CommandFactory::getInstace()->getCommand(CHECK_WINNER, &betScore));
		else if (command == "ICD")
			saveCom.push_back(CommandFactory::getInstace()->getCommand(INITIAL_CARD_DISTRIBUTION));
		else if (command == "PHR")
			saveCom.push_back(CommandFactory::getInstace()->getCommand(PERSONAL_HIT_REQUEST));
		else if (command == "R")
			saveCom.push_back(CommandFactory::getInstace()->getCommand(REPLAY));
		else if (command == "PSR")
			saveCom.push_back(CommandFactory::getInstace()->getCommand(PERSONAL_STOP_REQUEST));
	}
	this->replayLog.push_back(saveCom);
	this->gci->resetLog();
}

void App::AISetting() {
	while (1) {
		int AINum;
		cout << endl << endl;
		cout << "-----------------------------------------" << endl;
		cout << "<���� ���α׷�>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "AI ����" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "�÷��̾ �� ���� ��� ����AI������ �����մϴ�." << endl;
		cout << "���� �����̹Ƿ� ���� ������ �����ϴ�." << endl << endl;
		cout << "�÷��� �� AI�� ���� �����Ͽ� �ֽʽÿ�.(�ִ� 5)" << endl;
		cout << "���� ����: 0" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "-> ";

		cin >> AINum;
		system("cls");

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "�߸��� �Է��Դϴ�.";
			continue;
		}
		else if (AINum == 0) {
			return;
		}
		else if(AINum < 6 && AINum > 0){
			for (int i = 0; i < AINum; i++) {
				this->playerList.push_back(new User(AI, "", "AI_" + to_string(i), INIT_SCORE));
			}
		}
		else {
			cout << "�߸��� �Է��Դϴ�.";
			continue;
		}
		break;
	}
}

void App::settingOrder() {
	int command;
	bool isRandom;
	while (1) {
		cout << endl << endl;
		cout << "-----------------------------------------" << endl;
		cout << "<���� ���α׷�>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "�÷��� ����" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "1. �α��� ����" << endl;
		cout << "2. ����" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "-> ";

		cin >> command;
		system("cls");

		if (cin.fail() || command > 2 || command < 1) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "�߸��� �Է��Դϴ�.";
			continue;
		}
		isRandom = command - 1;

		if (isRandom) {
			srand((u_int)time(NULL));
			int random;
			for (u_int i = alivePlayerList.size(); i > 1; i--) {
				User* temp;
				random = rand() % i;

				temp = alivePlayerList[i-1];
				alivePlayerList[i-1] = alivePlayerList[random];
				alivePlayerList[random] = temp;
			}
		}
		for (int i = DELAY; i > 0; i--) {
			cout << endl << endl;
			cout << "-----------------------------------------" << endl;
			cout << "<���� ���α׷�>" << endl;
			cout << "-----------------------------------------" << endl;
			cout << "�÷��� ����" << endl;
			cout << "-----------------------------------------" << endl;

			for (u_int i = 0; i < alivePlayerList.size(); i++)
				cout << i + 1 << ". " << alivePlayerList[i]->getName() << "��" << endl;

			cout << "-----------------------------------------" << endl;
			cout << i << "�� �� ������ �����մϴ�.";
			Sleep(1000);
			system("cls");
		}
		return;
	}
}

int App::bettingScore() {
	int command;
	int limit = INIT_SCORE;

	while (1) {
		cout << endl << endl;
		cout << "-----------------------------------------" << endl;
		cout << "<���� ���α׷�>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "���� ����" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "������ ������ �Է��Ͽ� �ֽʽÿ�." << endl;

		for (User* user : alivePlayerList) {
			if (user->getScore() < limit) {
				limit = user->getScore();
			}
		}

		cout << "������ �ִ� ���� ������ " << limit << "���Դϴ�." << endl;
		cout << "���� ����: 0" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "-> ";

		cin >> command;  
		system("cls");

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "�߸��� �Է��Դϴ�.";
			continue;
		}
		else if (command > limit) {
			cout << "���� ������ �ʹ� Ů�ϴ�." << limit << "�� ���Ϸ� ������ �ֽʽÿ�.";
			continue;
		}
		else if (command < 0) {
			cout << "������ 0�� �̸����� �� �� �����ϴ�.";
			continue;
		}
		return command;		
	}
}

void App::gameProcedure() {
	while (this->alivePlayerList.size()) {
		for (u_int i = 0; i < alivePlayerList.size(); i++) {
			bool proceed;
			bool flag = true;
			bool misInput = false;
			int command;

			while (flag) {
				if (alivePlayerList[i]->getID() != AI) {//�÷��̾� ó��
					for (int j = DELAY; j >= 0; j--) {
						if (misInput)
							cout << "�߸��� �Է��Դϴ�.";

						cout << endl << endl;
						cout << "-----------------------------------------" << endl;
						cout << "<���� ���α׷�>" << endl;
						cout << "-----------------------------------------" << endl;
						cout << "���� ����" << endl;
						cout << "-----------------------------------------" << endl;
						cout << alivePlayerList[i]->getName() << "�� �����Դϴ�." << endl << endl;
						cout << "�Ʒ��� ������ �ִ� ���Դϴ�." << endl;
						cout << "-----------------------------------------" << endl << "\n\n\n\n\n\n\n\n";
	
						if (j != 0) {
							if (!misInput) {
								cout << endl << "-----------------------------------------" << endl;
								cout << j << "�� �� ī�� ����� ǥ�õ˴ϴ�.";
								Sleep(1000);
							}
							system("cls");
						}
					}

					for (u_int j = 0; j < alivePlayerList[i]->getUserCard().size(); j++) {
						Sleep(PRINT_DELAY);
						alivePlayerList[i]->getUserCard()[j]->CardPrint(100*j, 0);
					}

					cout << "���� ī����� ����(����ȭ): " << alivePlayerList[i]->getCardScore() << endl;
					cout << "-----------------------------------------" << endl;
					cout << "0. �� �׸� �ޱ�" << endl;
					cout << "1. ���� �� �ޱ�" << endl;
					cout << "-----------------------------------------" << endl;
					cout << "-> ";

					cin >> command;
					system("cls");

					misInput = false;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(100, '\n');
						misInput = true;
						continue;
					}
				}
				else { //AI ��Ŀ����
					srand((u_int)time(NULL));
					if ((alivePlayerList[i]->getCardScore() <= 11) || ((21 - alivePlayerList[i]->getCardScore()) > (rand() % 13 + 1)))
						command = 1;
					else
						command = 0;
				}
				switch (command) {
				case 0:
				case 1:
					proceed = command;
					flag = false;
					break;
				default:
					misInput = true;
				}
			}

			if (proceed) {
				u_int beforeNum = alivePlayerList.size();
				
				this->gci->getCommand(CommandFactory::getInstace()->getCommand(PERSONAL_HIT_REQUEST, &i));
				this->gci->executeCommand();

				this->gci->getCommand(CommandFactory::getInstace()->getCommand(CHECK_LOSER));
				this->gci->executeCommand();
				
				if (beforeNum > alivePlayerList.size())
					--i;
			}
			else {
				this->gci->getCommand(CommandFactory::getInstace()->getCommand(PERSONAL_STOP_REQUEST, &i));
				this->gci->executeCommand();
				--i;
			}
		}
	}
}