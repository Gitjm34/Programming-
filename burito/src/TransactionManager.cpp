
#include "TransactionManager.h"
#include "BuritoFactory.h"

#include <iostream>
#include <fstream>

using namespace std;

/*
class TransactionManager
{
private:
	vector<Transaction> orderTransactions;
	// order ID count, for application.
	int globalOrderID;
};
// */

// -------------------------------
// constructor, assign operator, etc.
// -------------------------------
TransactionManager::TransactionManager() {
	globalOrderID = 1;
}
TransactionManager::TransactionManager(const TransactionManager &input) {
	globalOrderID = input.globalOrderID;
	orderTransactions = input.orderTransactions;
}
TransactionManager::TransactionManager(TransactionManager &&input) {
	globalOrderID = move(input.globalOrderID);
	orderTransactions = move(input.orderTransactions);
}
TransactionManager& TransactionManager::operator=(
		const TransactionManager& input
		) {
	if (this == &input) { return *this; }
	globalOrderID = input.globalOrderID;
	orderTransactions = input.orderTransactions;
	return *this;
}
TransactionManager& TransactionManager::operator=(
		TransactionManager&& input
		) {
	if (this == &input) { return *this; }
	globalOrderID = move(input.globalOrderID);
	swap(orderTransactions, input.orderTransactions);
	return *this;
}
TransactionManager::~TransactionManager() { ; }
TransactionManager* TransactionManager::copyobj() const {
	return new TransactionManager(*this);
}



// -------------------------------
// methods
// -------------------------------

bool TransactionManager::isEmpty() const {
	return orderTransactions.empty();
}
void TransactionManager::addTransactionFromBurito(Burito* burito, bool saveToFile) {
	// -------------------------------
	// Add 'Transaction' to 'TransactionManager'
	// -------------------------------

	// make 'Transaction' object.

	Transaction *pTransaction = NULL;
	try {
		pTransaction = new Transaction(globalOrderID);
	} catch (const exception &e) {
		// destroy 'burito', and re-throw exception.
		delete burito;
		throw e;
	}

	// set 'burito' to '*pTransaction'.

	try {
		// NOTE:
		// after this, 'delete' operation for 'burito',
		//   will be executed at ("*pTransaction")'s destroyer,
		//   even if this function throws exception like memory allocation error.
		pTransaction->setOrderedMenu(burito);
	} catch (const exception &e) {
		// destroy 'pTransaction', and re-throw exception.
		delete pTransaction;
		throw e;
	}
	
	try {
		// NOTE:
		// After this, program should not access '*pTransaction',
		//   because this function call 'std::move(*pTransaction)',
		//   to add 'Transaction' type object at 'vector<Transaction>' type.
		addTransaction(pTransaction);
	} catch (const exception &e) {
		// destory 'pTransaction',
		//   which was dinamically allocated & moved,
		//   and re-throw exception.
		delete pTransaction;
		throw e;
	}
	// destory 'pTransaction',
	//   which was dinamically allocated & moved.
	delete pTransaction;

	// ;
	globalOrderID++;

	// Save Transactions to file.
	if (saveToFile) {
		writeTransaction();
	}
}
int TransactionManager::addTransactionFromIngrInfo(
		const vector<int> &ingrInfo, bool saveToFile) {
	// -------------------------------
	// Add 'Transaction' to 'TransactionManager'
	// -------------------------------

	// make 'Transaction' object.

	Transaction *pTransaction = NULL;
	pTransaction = new Transaction(globalOrderID);

	// set 'Ingredients' list to '*pTransaction'.

	try {
		int result = pTransaction->setIngredientsInfo(ingrInfo);
		if (result != 0) {
			// CASE OF: integer value of 'ingrInfo' is wrong.
			delete pTransaction;
			return 1;
		}
	} catch (const exception &e) {
		// destroy 'pTransaction', and re-throw exception.
		delete pTransaction;
		throw e;
	}
	
	try {
		// NOTE:
		// After this, program should not access '*pTransaction',
		//   because this function call 'std::move(*pTransaction)',
		//   to add 'Transaction' type object at 'vector<Transaction>' type.
		addTransaction(pTransaction);
	} catch (const exception &e) {
		// destory 'pTransaction',
		//   which was dinamically allocated & moved,
		//   and re-throw exception.
		delete pTransaction;
		throw e;
	}
	// destory 'pTransaction',
	//   which was dinamically allocated & moved.
	delete pTransaction;

	// ;
	globalOrderID++;

	// Save Transactions to file.
	if (saveToFile) {
		writeTransaction();
	}

	return 0;
}
void TransactionManager::addTransaction(Transaction* newTransaction) {
	orderTransactions.push_back(move(*newTransaction));
}

void TransactionManager::processFrontTransaction() {
	if (orderTransactions.empty()) {
		cout << "주문 없음!" << endl;
		return;
	}

	Transaction & transaction = orderTransactions.front();
	const Burito* burito = transaction.getOrderedMenu();
	if (burito != NULL) {
		cout << "주분 처리!" << endl;
		cout << "---------- 주문 내용 ----------" << endl;
		cout << "주문 ID: " << transaction.getOrderID() << endl;
		cout << "---------- 상세 내용 ----------" << endl;
		cout << burito->getDescription() << endl;
		cout << "가격: " << burito->getCost() << "원" << endl;

		orderTransactions.erase(orderTransactions.begin());
		cout << "처리 완료!" << endl;
		return;
	}
	cout << "주문 값 오류!?" << endl;
}

void TransactionManager::printTransaction() const {
	int index = 1;
	vector<Transaction>::const_iterator iter_begin, iter_end;
	iter_begin = orderTransactions.begin();
	iter_end = orderTransactions.end();

	cout << "---------- 주문 목록 ----------" << endl;
	for (; iter_begin != iter_end; iter_begin++, index++) {
		// FOR: every '*iter_begin', type 'Transaction'.

		cout << index << ". 주문ID(" << iter_begin->getOrderID() << ") ";
		
		const Burito* burito = iter_begin->getOrderedMenu();
		if (burito == NULL) {
			cout << "주문 값 오류!?" << endl;
			continue;
		}

		string lineDescription =
			BuritoFactory::makeLineDescription(burito->getIngredientsInfo());
		if (lineDescription.empty()) {
			cout << "주문 값 오류!?" << endl;
			continue;
		}
		cout << lineDescription << endl;

	}
	cout << "-------------------------------" << endl;
}
void TransactionManager::deleteTransaction(int index) {
	if (index < 0 || orderTransactions.size() <= (size_t)index) {
		cout << "인덱스 값 오류!" << endl;
		return;
	}
	orderTransactions.erase(orderTransactions.begin() + (size_t)index);
	cout << "처리 완료!" << endl;
}

void TransactionManager::readTransaction() {
	// -------------------------------
	// open file
	// -------------------------------

	ifstream fileIn;
	fileIn.open("./Order.txt");
	if (!fileIn.is_open()) {
		cout << "파일 읽기: 이전에 저장된 주문 목록 파일이 없습니다." << endl;
		return;
	}


	// -------------------------------
	// read from file
	// -------------------------------

	// Read order.
	
	size_t orderSize;
	// Read next order's size.
	fileIn >> orderSize;
	while (!fileIn.eof()) {
		if (fileIn.fail()) {
			cout << "파일 읽기: 값 오류로 읽기를 중단합니다." << endl;
			return;
		}
		if (fileIn.bad()) {
			cout << "파일 읽기: 예상치 못한 입출력 에러로 인해 읽기를 중단합니다." << endl;
			return;
		}

		// Read one order (one line).

		int typeOrIngrValue;
		vector<int> ingredientsInfo;
		for (size_t i = (size_t)0; i < orderSize; i++) {
			fileIn >> typeOrIngrValue;
			if (fileIn.fail()) {
				cout << "파일 읽기: 값 오류로 읽기를 중단합니다." << endl;
				return;
			}
			if (fileIn.bad()) {
				cout << "파일 읽기: 예상치 못한 입출력 에러로 인해 읽기를 중단합니다." << endl;
				return;
			}
			ingredientsInfo.push_back(typeOrIngrValue);
		}

		// Add Transaction.

		int result = addTransactionFromIngrInfo(ingredientsInfo, false);
		if (result != 0) {
			cout << "파일 읽기: 주문 목록의 비정상적인 숫자 값으로 인해 읽기를 중단합니다." << endl;
			return;
		}

		// Read next order's size
		fileIn >> orderSize;
	}


	// -------------------------------
	// close file
	// -------------------------------

	fileIn.close();
}
void TransactionManager::writeTransaction() const {
	// -------------------------------
	// open file
	// -------------------------------

	ofstream fileOut;
	fileOut.open("./Order.txt");
	if (!fileOut.is_open()) {
		cout << "LOG: ERROR: Cannot open the file for write." << endl;
		return;
	}

	// -------------------------------
	// write to file
	// -------------------------------

	vector<Transaction>::const_iterator iter_begin, iter_end;
	iter_begin = orderTransactions.begin();
	iter_end = orderTransactions.end();

	for (; iter_begin != iter_end; iter_begin++) {
		// FOR: every '*iter_begin', type 'Transaction'.

		const vector<int> *pIngredientsInfo =
			&(iter_begin->getIngredientsInfo());
		vector<int>::const_iterator iterIngr_begin, iterIngr_end;
		iterIngr_begin = pIngredientsInfo->begin();
		iterIngr_end = pIngredientsInfo->end();
		
		// write the size of IngredientsInfo to file.
		fileOut << pIngredientsInfo->size();
		if (pIngredientsInfo->size() == (size_t)0) {
			fileOut << endl;
			continue;
		}

		// write the 'IngredientsInfo' to file.
		fileOut << "\t" << *iterIngr_begin; // first number.
		for (iterIngr_begin++; iterIngr_begin != iterIngr_end; iterIngr_begin++) {
			fileOut << "\t" << *iterIngr_begin;
		}
		fileOut << endl; // next line.
	}

	// -------------------------------
	// close file
	// -------------------------------

	fileOut.close();
}

//EOF

