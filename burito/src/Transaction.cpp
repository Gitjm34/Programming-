
#include "Transaction.h"
#include "BuritoFactory.h"

using namespace std;

/*
class Transaction
{
private:
	int orderID;
	vector<int> ingredientsInfo;
	Burito* orderedMenu;
};
// */

// -------------------------------
// constructor, assign operator, etc.
// -------------------------------
Transaction::Transaction(int orderID) {
	this->orderID = orderID;
	orderedMenu = NULL;
}
Transaction::Transaction(const Transaction &input) {
	orderID = input.orderID;
	ingredientsInfo = input.ingredientsInfo;
	orderedMenu = input.orderedMenu->copyobj();
}
Transaction::Transaction(Transaction &&input) {
	orderID = move(input.orderID);
	ingredientsInfo = move(input.ingredientsInfo);
	orderedMenu = move(input.orderedMenu);
	input.orderedMenu = NULL;
}
Transaction& Transaction::operator=(
		const Transaction& input
		) {
	if (this == &input) { return *this; }
	orderID = input.orderID;
	ingredientsInfo = input.ingredientsInfo;
	if (orderedMenu != NULL) {
		delete orderedMenu;
		// This NULL assignment is for,
		//   the case of Exception in function '.copyobj()' below.
		orderedMenu = NULL;
	}
	orderedMenu = input.orderedMenu->copyobj();
	return *this;
}
Transaction& Transaction::operator=(
		Transaction&& input
		) {
	if (this == &input) { return *this; }
	orderID = move(input.orderID);
	ingredientsInfo = move(input.ingredientsInfo);
	swap(orderedMenu, input.orderedMenu);
	return *this;
}
Transaction::~Transaction() {
	if (orderedMenu != NULL) { delete orderedMenu; }
}
Transaction* Transaction::copyobj() const {
	return new Transaction(*this);
}




// -------------------------------
// methods
// -------------------------------

void Transaction::setOrderedMenu(Burito *orderedMenu) {
	if (this->orderedMenu != NULL) { delete this->orderedMenu; }
	this->orderedMenu = orderedMenu;

	// Set 'ingredientsInfo'

	if (this->orderedMenu == NULL) {
		this->ingredientsInfo.clear();
	}
	else {
		this->ingredientsInfo = orderedMenu->getIngredientsInfo();
	}
}

int Transaction::setIngredientsInfo(const vector<int> &ingredientsInfo) {
	this->ingredientsInfo = ingredientsInfo;
	return remakeOrderedMenu();
}

int Transaction::setIngredientsInfo(vector<int> &&ingredientsInfo) {
	this->ingredientsInfo = move(ingredientsInfo);
	return remakeOrderedMenu();
}

int Transaction::remakeOrderedMenu() {
	Burito *ordered = BuritoFactory::makeOrderedMenu(ingredientsInfo);
	if (orderedMenu != NULL) { delete orderedMenu; }
	orderedMenu = ordered;

	// If one of the type value of 'ingredientsInfo' is wrong,
	//   'orderedMenu' will be NULL,
	//   and return value will be 1.
	// Return 0 if success.
	return orderedMenu == NULL ? 1 : 0;
}

//EOF


