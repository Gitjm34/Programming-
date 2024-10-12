
#include "Jumbo.h"

using namespace std;



// -------------------------------
// constructor, assign operator, etc.
// -------------------------------

Jumbo::Jumbo(Burito* decoBurito) :
	Decorator(decoBurito)
{
	;
}
Jumbo::Jumbo() { ; }
Jumbo::Jumbo(const Jumbo &input) :
	Decorator(input)
{
	;
}
Jumbo::Jumbo(Jumbo &&input) :
	Decorator(move(input))
{
	;
}
Jumbo& Jumbo::operator=(const Jumbo& input) {
	Decorator::operator=(input);
	return *this;
}
Jumbo& Jumbo::operator=(Jumbo&& input) {
	Decorator::operator=(move(input));
	return *this;
}
Jumbo::~Jumbo() {
	;
}
Burito* Jumbo::copyobj() const {
	return new Jumbo(*this);
}

Jumbo::Jumbo(const Jumbo &input, Burito* decoBurito) :
	Decorator(input, decoBurito)
{
	;
}
Burito* Jumbo::copyobjExceptDeco(Burito* decoBurito) const {
	return new Jumbo(*this, decoBurito);
}



// -------------------------------
// methods
// -------------------------------

int Jumbo::getCostSelf() const {
	return 1000;
}

string Jumbo::getDescriptionSelf() const {
	return string("점보: 1000");
}

int Jumbo::getIngredientInfoSelf() const {
	return 1;
}

//EOF


