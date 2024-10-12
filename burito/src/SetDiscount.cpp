

#include "SetDiscount.h"

using namespace std;



// -------------------------------
// constructor, assign operator, etc.
// -------------------------------

SetDiscount::SetDiscount(Burito* decoBurito) :
	Decorator(decoBurito)
{
	;
}
SetDiscount::SetDiscount() { ; }
SetDiscount::SetDiscount(const SetDiscount &input) :
	Decorator(input)
{
	;
}
SetDiscount::SetDiscount(SetDiscount &&input) :
	Decorator(move(input))
{
	;
}
SetDiscount& SetDiscount::operator=(const SetDiscount& input) {
	Decorator::operator=(input);
	return *this;
}
SetDiscount& SetDiscount::operator=(SetDiscount&& input) {
	Decorator::operator=(move(input));
	return *this;
}
SetDiscount::~SetDiscount() {
	;
}
Burito* SetDiscount::copyobj() const {
	return new SetDiscount(*this);
}

SetDiscount::SetDiscount(const SetDiscount &input, Burito* decoBurito) :
	Decorator(input, decoBurito)
{
	;
}
Burito* SetDiscount::copyobjExceptDeco(Burito* decoBurito) const {
	return new SetDiscount(*this, decoBurito);
}



// -------------------------------
// methods
// -------------------------------

int SetDiscount::getCostSelf() const {
	return -500;
}

string SetDiscount::getDescriptionSelf() const {
	return string("세트할인: -500");
}

int SetDiscount::getIngredientInfoSelf() const {
	return 3;
}

//EOF


