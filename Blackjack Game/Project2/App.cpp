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
		cout << "<블랙잭 프로그램>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "사용자 여러분 반갑습니다!" << endl;
		cout << "-----------------------------------------" << endl;

		if (this->playerList.size() == 0) {
			cout << "1. 로그인" << endl;
			cout << "2. 회원가입" << endl;
		}
		else {
			cout << "최대 플레이어 수: 6" << endl;
			cout << "현재 플레이어 수: " << playerList.size() << endl;
			cout << "-----------------------------------------" << endl;
			cout << "1. 로그인" << endl;
			cout << "2. 회원가입" << endl;
			cout << "3. 게임 시작" << endl;
			cout << "4. 리플레이 보기" << endl;
			cout << "5. 유저 정보 보기" << endl;
			cout << "6. 로그아웃" << endl;
		}

		cout << "0. 프로그램 종료" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "-> ";

		cin >> command;
		system("cls");

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "잘못된 입력입니다.";
			continue;
		}

		switch (command) {
		case 0:
			cout << "갑사합니다!" << endl;
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
			cout << "잘못된 입력입니다.";
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
			cout << "<블랙잭 프로그램>" << endl;
			cout << "-----------------------------------------" << endl;
			cout << "로그인" << endl;
			cout << "-----------------------------------------" << endl;
			cout << "아이디를 입력하여 주십시오" << endl;
			cout << "id -> ";
			cin >> id;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(100, '\n');
				system("cls");
				cout << "잘못된 입력입니다.";
				continue;
			}

			cout << "-----------------------------------------" << endl;
			cout << "비밀번호를 입력하여 주십시오." << endl;
			cout << "Password -> ";
			cin >> pw;
			system("cls");

			for (User* user : this->userList) {
				if (user->getID() == id && user->getPW() == pw) {
					for (User* check_user : this->playerList) {
						if (user == check_user) {
							cout << "이미 로그인된 유저입니다.";
							return;
						}
					}
					this->playerList.push_back(user);
					return;
				}
			}

			cout << "ID 혹은 Password가 잘못되었습니다.";
			return;
		}
	}
	else
		cout << "플레이어 수는 6명을 넘을 수 없습니다.";
}

void App::logout() {
	u_int command;

	while (1) {
		cout << endl << endl;
		cout << "-----------------------------------------" << endl;
		cout << "<블랙잭 프로그램>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "로그아웃" << endl;
		cout << "-----------------------------------------" << endl;

		int i = 1;
		for (User* user : this->playerList) {
			cout << i << ". \"" << user->getName() << "\"님" << endl;
			++i;
		}
		cout << "0. 뒤로가기" << endl;

		cout << "-----------------------------------------" << endl;
		cout << "-> ";
		cin >> command;
		system("cls");

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "잘못된 입력입니다.";
		}
		else if (command == 0) {
			return;
		}
		else if (command > 0 && command <= this->playerList.size()) {
			this->playerList.erase(this->playerList.begin() + command - 1);
		}
		else
			cout << "잘못된 입력입니다.";
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
		cout << "<블랙잭 프로그램>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "회원가입" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "가입할 id: ";
		cin >> id;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			system("cls");
			cout << "잘못된 입력입니다.";
			continue;
		}
		for (User* user : userList) {
			if (user->getID() == id) {
				system("cls");
				cout << "중복되는 ID가 존재합니다.";
				duplication = true;
			}
		}
		if (duplication)
			continue;
		
		cout << "가입할 pw(비밀번호): ";
		cin >> pw;

		cout << "사용자님의 이름: ";
		cin >> name;

		this->userList.push_back(new User(id, pw, name, INIT_SCORE));
		system("cls");

		cout << "성공적으로 가입되었습니다.";
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
		cout << "user.txt.파일을 읽는데에 실패했습니다." << endl;
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
		cout << "replay.txt 파일을 읽는데 실패했습니다." << endl;
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
   /////////////////////////////////////////////////////////////////////초기세팅//////////////////////////////////////////////////////////////////////////
   *******************************************************************************************************************************************************/
	//플레이어순서설정, 카드섞기, 베팅점수설정, AI설정
	//이후 리플레이 벡터에 해당 정보들 push

	int betScore = 0;
	vector<UserScoreInfo> score;

	if (this->playerList.size() == 1) {
		this->AISetting();
		if (this->playerList.size() == 1) //AI가 추가되지 않았을 경우. 즉, "게임중지"를 선택한 경우
			return;
	}
	else {
		betScore = this->bettingScore(); //베팅점수 설정
		if (!betScore) {
			return;
		}
	}

	alivePlayerList = playerList;
	this->settingOrder(); //순서 설정(로그인순 or 랜덤)
	this->suffleDeck(); //카드섞기

	vector<Card*> saveDeck;
	vector<User*> savePlayerList;

	for (Card* card : deck)
		saveDeck.push_back(new Card(*card));
	for (User* user : alivePlayerList)
		savePlayerList.push_back(new User(*user));

	this->shuffledDeckForReplay.push_back(saveDeck); //리플레이 카드덱 추가
	this->playerListForReplay.push_back(savePlayerList); //리플레이 플레이어리스트 추가
	
	this->betScoreForReplay.push_back(betScore);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*******************************************************************************************************************************************************
	/////////////////////////////////////////////////////////////////////게임시작//////////////////////////////////////////////////////////////////////////
	*******************************************************************************************************************************************************/
	//커맨드 초기화
	//이후 InitialCardDistribution 커맨드 실시 후 게임 시작.
	//마지막으로 CheckWinner커맨드 실행 후 각 리스트 초기화 및 커맨드리스트 리플레이벡터에 추가.

	Command::initialize(&this->alivePlayerList, &this->deck, &this->scorePQ);

	this->gci->getCommand(CommandFactory::getInstace()->getCommand(INITIAL_CARD_DISTRIBUTION));
	this->gci->executeCommand();
	
	this->gameProcedure(); //게임 진행함수. 내부진행은 커맨드패턴으로 구현.

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

void App::showReplay() { //메뉴 출력은 여기서 하고 관련 커맨드 벡터만 리플레이로 넘긴 후 끝.
	vector<void*> replayData;
	int command;

	while (1) {
		cout << endl << endl;
		cout << "-----------------------------------------" << endl;
		cout << "<블랙잭 프로그램>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "리플레이 보기" << endl;
		cout << "-----------------------------------------" << endl << endl;
		
		for (u_int i = 0; i < playerListForReplay.size(); i++) {
			cout << i + 1 << ".";
			for (User* user : playerListForReplay[i]) {
				cout << " [" << user->getName() << "]";
			}
			cout << endl << "베팅점수 " <<  this->betScoreForReplay[i] << "점의 게임" << endl << endl;
		}

		cout << "0. 뒤로 가기" << endl << endl;
		cout << "-----------------------------------------" << endl;
		cout << "감상할 리플레이-> ";
		

		cin >> command;
		system("cls");

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "잘못된 입력입니다.";
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
			cout << "잘못된 입력입니다.";
		}
	}
	gci->resetLog();
}

void App::showUserInfo() {
	string dummy;

	cout << endl << endl;
	cout << "-----------------------------------------" << endl;
	cout << "<블랙잭 프로그램>" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "유저 점수 보기" << endl;
	cout << "-----------------------------------------" << endl << endl;
	cout << "이름\t남은 점수" << endl << endl;

	for (User* user : playerList) {
		user->printMyInformation();
	}

	cout << "-----------------------------------------" << endl;
	cout << "계속 하시려면 아무 키나 입력하여 주십시오. ";
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
		cout << "<블랙잭 프로그램>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "AI 설정" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "플레이어가 한 명일 경우 연습AI전만이 가능합니다." << endl;
		cout << "연습 게임이므로 점수 증감은 없습니다." << endl << endl;
		cout << "플레이 할 AI의 수를 설정하여 주십시오.(최대 5)" << endl;
		cout << "게임 중지: 0" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "-> ";

		cin >> AINum;
		system("cls");

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "잘못된 입력입니다.";
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
			cout << "잘못된 입력입니다.";
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
		cout << "<블랙잭 프로그램>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "플레이 순서" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "1. 로그인 순서" << endl;
		cout << "2. 랜덤" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "-> ";

		cin >> command;
		system("cls");

		if (cin.fail() || command > 2 || command < 1) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "잘못된 입력입니다.";
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
			cout << "<블랙잭 프로그램>" << endl;
			cout << "-----------------------------------------" << endl;
			cout << "플레이 순서" << endl;
			cout << "-----------------------------------------" << endl;

			for (u_int i = 0; i < alivePlayerList.size(); i++)
				cout << i + 1 << ". " << alivePlayerList[i]->getName() << "님" << endl;

			cout << "-----------------------------------------" << endl;
			cout << i << "초 후 게임을 시작합니다.";
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
		cout << "<블랙잭 프로그램>" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "점수 베팅" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "베팅할 점수를 입력하여 주십시오." << endl;

		for (User* user : alivePlayerList) {
			if (user->getScore() < limit) {
				limit = user->getScore();
			}
		}

		cout << "가능한 최대 베팅 점수는 " << limit << "점입니다." << endl;
		cout << "게임 중지: 0" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "-> ";

		cin >> command;  
		system("cls");

		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "잘못된 입력입니다.";
			continue;
		}
		else if (command > limit) {
			cout << "베팅 점수가 너무 큽니다." << limit << "점 이하로 설정해 주십시오.";
			continue;
		}
		else if (command < 0) {
			cout << "베팅은 0점 미만으로 할 수 없습니다.";
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
				if (alivePlayerList[i]->getID() != AI) {//플레이어 처리
					for (int j = DELAY; j >= 0; j--) {
						if (misInput)
							cout << "잘못된 입력입니다.";

						cout << endl << endl;
						cout << "-----------------------------------------" << endl;
						cout << "<블랙잭 프로그램>" << endl;
						cout << "-----------------------------------------" << endl;
						cout << "블랙잭 게임" << endl;
						cout << "-----------------------------------------" << endl;
						cout << alivePlayerList[i]->getName() << "님 차례입니다." << endl << endl;
						cout << "아래는 가지고 있는 패입니다." << endl;
						cout << "-----------------------------------------" << endl << "\n\n\n\n\n\n\n\n";
	
						if (j != 0) {
							if (!misInput) {
								cout << endl << "-----------------------------------------" << endl;
								cout << j << "초 후 카드 목록이 표시됩니다.";
								Sleep(1000);
							}
							system("cls");
						}
					}

					for (u_int j = 0; j < alivePlayerList[i]->getUserCard().size(); j++) {
						Sleep(PRINT_DELAY);
						alivePlayerList[i]->getUserCard()[j]->CardPrint(100*j, 0);
					}

					cout << "현재 카드숫자 총합(최적화): " << alivePlayerList[i]->getCardScore() << endl;
					cout << "-----------------------------------------" << endl;
					cout << "0. 패 그만 받기" << endl;
					cout << "1. 다음 패 받기" << endl;
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
				else { //AI 메커니즘
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