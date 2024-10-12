
#include "ComboDiscount.h"

using namespace std;



// -------------------------------
// constructor, assign operator, etc.
// -------------------------------

ComboDiscount::ComboDiscount(Burito* decoBurito) :
	Decorator(decoBurito)
{
	;
}
ComboDiscount::ComboDiscount() { ; }
ComboDiscount::ComboDiscount(const ComboDiscount &input) :
	Decorator(input)
{
	;
}
ComboDiscount::ComboDiscount(ComboDiscount &&input) :
	Decorator(move(input))
{
	;
}
ComboDiscount& ComboDiscount::operator=(const ComboDiscount& input) {
	Decorator::operator=(input);
	return *this;
}
ComboDiscount& ComboDiscount::operator=(ComboDiscount&& input) {
	Decorator::operator=(move(input));
	return *this;
}
ComboDiscount::~ComboDiscount() {
	;
}
Burito* ComboDiscount::copyobj() const {
	return new ComboDiscount(*this);
}

ComboDiscount::ComboDiscount(const ComboDiscount &input, Burito* decoBurito) :
	Decorator(input, decoBurito)
{
	;
}
Burito* ComboDiscount::copyobjExceptDeco(Burito* decoBurito) const {
	return new ComboDiscount(*this, decoBurito);
}



// -------------------------------
// methods
// -------------------------------

int ComboDiscount::getCostSelf() const {
	return -300;
}

string ComboDiscount::getDescriptionSelf() const {
	return string("콤보할인: 300");
}

int ComboDiscount::getIngredientInfoSelf() const {
	return 2;
}

//EOF


