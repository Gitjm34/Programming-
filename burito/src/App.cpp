
#include "App.h"

#include <iostream>
#include <stdexcept>
#include <climits>

using namespace std;

/*
class App
{
private:
	BuritoFactory* bf;
	TransactionManager* tm;
};
// */

App::App() {
	bf = new BuritoFactory(); // not used for now.
	tm = new TransactionManager();
}
App::~App() {
	delete bf;
	delete tm;
}


void App::run() {
	// set utf-8 output mode (for MSVC)
#ifdef _MSC_VER
	setlocale(LC_CTYPE, ".UTF-8");
	std::locale::global(
			std::locale(
				std::locale::classic(),
				std::locale(".UTF-8"),
				std::locale::ctype
			)
	);
#endif

	try {
		bool end_requested = false;
		readTransaction(); // load Transactions from file.

		// LOOP: main loop for the order management program.
		while (!end_requested) {

			cout << "부리또 주문 관리 프로그램" << endl;
			// print transaction list.
			printTransaction();

			// Read user interaction value of top menu.
			MenuV menuV = processTopMenu();
			switch (menuV) {
				case MenuV::ADD:
					addTransaction();
					break;
				case MenuV::CANCEL:
					cancelTransaction();
					break;
				case MenuV::PRT:
					processFrontTransaction();
					break;
				case MenuV::EXIT:
					end_requested = true;
					break;
				case MenuV::INVALID:
					(void)0;
					break;
			}
		}
		// END_LOOP: main loop for the order management program.

		writeTransaction();
		cout << "부리또 주문 관리 프로그램 정상 종료" << endl;
	}
	catch (const std::exception &e) {
		cerr << e.what();
	}
}


App::MenuV App::processTopMenu() const {
	cout << "1. 주문 추가\n";
	cout << "2. 주문 취소\n";
	cout << "3. 주문 처리\n";
	cout << "4. 프로그램 종료" << endl;
	cout << ": ";
	int userInput;
	cin >> userInput; cout << endl;
	
	if (cin.eof()) {
		return MenuV::EXIT;
	}
	if (cin.fail()) {
		cout << "잘못된 입력입니다, 정수를 입력하세요" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return MenuV::INVALID;
	}
	if (userInput < 1 || 4 < userInput) {
		cout << "잘못된 숫자 입력입니다" << endl;
		return MenuV::INVALID;
	}

	switch (userInput) {
		case 1:
			return MenuV::ADD;
		case 2:
			return MenuV::CANCEL;
		case 3:
			return MenuV::PRT;
		case 4:
			return MenuV::EXIT;
	}
	return MenuV::INVALID;
}

int App::processBaseBuritoMenu() const {
	cout << "-------------------------------" << endl;
	cout << "메뉴 선택" << endl;
	cout << "1. 단품 (부리또, 3000원)" << endl;
	cout << "2. 콤보 (부리또 + 음료, 3700원)" << endl;
	cout << "3. 세트 (부리또 + 음료 + 감자튀김, 4500원)" << endl;
	cout << "-------------------------------" << endl;
	cout << ": ";
	int userInput;
	cin >> userInput; cout << endl;
	
	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return -1;
	}
	return userInput;
}

int App::processIngredientsMenu() const {
	cout << "추가 메뉴 선택" << endl;
	cout << "0. 그만 추가" << endl;
	cout << "1. 점보 (1000원)" << endl;
	cout << "2. 소세지 (1000원)" << endl;
	cout << "3. 음료수 (1000원)" << endl;
	cout << "4. 감자튀김 (2000원)" << endl;
	cout << "5. 그만 추가" << endl;
	cout << "-------------------------------" << endl;
	cout << ": ";
	int userInput;
	cin >> userInput; cout << endl;
	
	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return -1;
	}
	return userInput;
}

int App::processCancelMenu() const {
	// print transaction list.
	printTransaction();

	cout << "--원하는 '인덱스' 번호를 입력--" << endl;
	cout << ": ";
	int userInput;
	cin >> userInput; cout << endl;
	
	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return -1;
	}
	return userInput;
	;
	return 1;
}


void App::addTransaction() {

	// get base burito type.

	int baseBuritoType = processBaseBuritoMenu();
	Burito *burito = BuritoFactory::makeOrderedMenu(baseBuritoType);
	if (burito == NULL) {
		cout << "잘못된 값" << endl;
		return;
	}


	bool end_ingredients_loop = false;
	// LOOP: ingredientsInfo selection loop.
	while (!end_ingredients_loop) {
		// get ingredient type.
		int ingredientType = processIngredientsMenu();
		try {
			if (ingredientType == 0 || ingredientType == 5) {
				// CASE OF: stop (그만추가).
				end_ingredients_loop = true;
				continue;
			}
			Burito *newBurito = BuritoFactory::makeOrderedMenu(
					burito, ingredientType);
			if (newBurito == NULL) {
				// CASE OF: wrong value.
				cout << "잘못된 값" << endl;
			}
			else {
				// CASE OF: not wrong value ('newBurito' has 'burito' pointer).
				burito = newBurito;
			}
		} catch (const exception &e) {
			// destroy 'burito', and re-throw exception.
			delete burito;
			throw e;
		}
	}
	// END_LOOP: ingredientsInfo selection loop.


	// -------------------------------
	// Add 'Transaction' to 'TransactionManager'
	// -------------------------------

	tm->addTransactionFromBurito(burito, true);
}


void App::processFrontTransaction() {
	// This function will print result to 'stdout'.
	tm->processFrontTransaction();
	// Save Transactions to file.
	writeTransaction();
}

void App::cancelTransaction() {
	if (tm->isEmpty()) {
		cout << "삭제할 주문이 없습니다." << endl;
		return;
	}

	int indexOfList = processCancelMenu();
	indexOfList--; // fix the index, to make the index value starts with 0.
	// Delete Transaction, with index, starts with 0.
	// This function will print result to 'stdout'.
	tm->deleteTransaction(indexOfList);

	// Save Transactions to file.
	writeTransaction();
}


void App::printTransaction() const {
	// This function will print result to 'stdout'.
	tm->printTransaction();
}
void App::readTransaction() {
	tm->readTransaction();
}
void App::writeTransaction() const {
	tm->writeTransaction();
}


//EOF

