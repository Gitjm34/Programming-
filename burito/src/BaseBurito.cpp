
#include "BaseBurito.h"

#include <sstream>

using namespace std;

int BaseBurito::getCost() const {
	return 3000;
}

int BaseBurito::getCostSelf() const {
	return 3000;
}

string BaseBurito::getDescription() const {
	return string("부리또: 3000");
}

string BaseBurito::getDescriptionSelf() const {
	return string("부리또: 3000");
}

vector<int> BaseBurito::getIngredientsInfo() const {
	vector<int> ret;
	ret.push_back(1); // 단품.
	return ret;
}

int BaseBurito::getIngredientInfoSelf() const {
	return 1; // 단품.
}


Burito* BaseBurito::getDecoratedBurito() {
	return NULL;
}

const Burito* BaseBurito::getDecoratedBurito() const {
	return NULL;
}

vector<Burito*> BaseBurito::getAllDecoPointer() {
	vector<Burito*> ret;
	ret.push_back(this);
	return ret;
}

vector<const Burito*> BaseBurito::getAllDecoPointer() const {
	vector<const Burito*> ret;
	ret.push_back(this);
	return ret;
}

//EOF
