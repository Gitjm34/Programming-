
#include "Fries.h"

using namespace std;



// -------------------------------
// constructor, assign operator, etc.
// -------------------------------

Fries::Fries(Burito* decoBurito) :
	Decorator(decoBurito)
{
	;
}
Fries::Fries() { ; }
Fries::Fries(const Fries &input) :
	Decorator(input)
{
	;
}
Fries::Fries(Fries &&input) :
	Decorator(move(input))
{
	;
}
Fries& Fries::operator=(const Fries& input) {
	Decorator::operator=(input);
	return *this;
}
Fries& Fries::operator=(Fries&& input) {
	Decorator::operator=(move(input));
	return *this;
}
Fries::~Fries() {
	;
}
Burito* Fries::copyobj() const {
	return new Fries(*this);
}

Fries::Fries(const Fries &input, Burito* decoBurito) :
	Decorator(input, decoBurito)
{
	;
}
Burito* Fries::copyobjExceptDeco(Burito* decoBurito) const {
	return new Fries(*this, decoBurito);
}



// -------------------------------
// methods
// -------------------------------

int Fries::getCostSelf() const {
	return 2000;
}

string Fries::getDescriptionSelf() const {
	return string("감자튀김: 2000");
}

int Fries::getIngredientInfoSelf() const {
	return 4;
}

//EOF


