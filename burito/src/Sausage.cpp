
#include "Sausage.h"

using namespace std;



// -------------------------------
// constructor, assign operator, etc.
// -------------------------------

Sausage::Sausage(Burito* decoBurito) :
	Decorator(decoBurito)
{
	;
}
Sausage::Sausage() { ; }
Sausage::Sausage(const Sausage &input) :
	Decorator(input)
{
	;
}
Sausage::Sausage(Sausage &&input) :
	Decorator(move(input))
{
	;
}
Sausage& Sausage::operator=(const Sausage& input) {
	Decorator::operator=(input);
	return *this;
}
Sausage& Sausage::operator=(Sausage&& input) {
	Decorator::operator=(move(input));
	return *this;
}
Sausage::~Sausage() {
	;
}
Burito* Sausage::copyobj() const {
	return new Sausage(*this);
}

Sausage::Sausage(const Sausage &input, Burito* decoBurito) :
	Decorator(input, decoBurito)
{
	;
}
Burito* Sausage::copyobjExceptDeco(Burito* decoBurito) const {
	return new Sausage(*this, decoBurito);
}



// -------------------------------
// methods
// -------------------------------

int Sausage::getCostSelf() const {
	return 1000;
}

string Sausage::getDescriptionSelf() const {
	return string("소세지: 1000");
}

int Sausage::getIngredientInfoSelf() const {
	return 2;
}

//EOF


