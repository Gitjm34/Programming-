
#include "Drink.h"

using namespace std;



// -------------------------------
// constructor, assign operator, etc.
// -------------------------------

Drink::Drink(Burito* decoBurito) :
	Decorator(decoBurito)
{
	;
}
Drink::Drink() { ; }
Drink::Drink(const Drink &input) :
	Decorator(input)
{
	;
}
Drink::Drink(Drink &&input) :
	Decorator(move(input))
{
	;
}
Drink& Drink::operator=(const Drink& input) {
	Decorator::operator=(input);
	return *this;
}
Drink& Drink::operator=(Drink&& input) {
	Decorator::operator=(move(input));
	return *this;
}
Drink::~Drink() {
	;
}
Burito* Drink::copyobj() const {
	return new Drink(*this);
}

Drink::Drink(const Drink &input, Burito* decoBurito) :
	Decorator(input, decoBurito)
{
	;
}
Burito* Drink::copyobjExceptDeco(Burito* decoBurito) const {
	return new Drink(*this, decoBurito);
}



// -------------------------------
// methods
// -------------------------------

int Drink::getCostSelf() const {
	return 1000;
}

string Drink::getDescriptionSelf() const {
	return string("음료수: 1000");
}

int Drink::getIngredientInfoSelf() const {
	return 3;
}

//EOF


