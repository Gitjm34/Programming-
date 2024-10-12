
#include "Decorator.h"

#include <sstream>
#include <vector>

using namespace std;



/*
class Decorator : public Burito
{

protected:
	// pointer of parent, for decorator design pattern.
	Burito* decoratedBurito;
};
// */


// -------------------------------
// constructor, assign operator, etc.
// -------------------------------

Decorator::Decorator(Burito* decoBurito) {
	decoratedBurito = decoBurito;
}
Decorator::Decorator() {
	decoratedBurito = NULL;
}
Decorator::Decorator(const Decorator &input) {
	if (input.decoratedBurito == NULL) {
		decoratedBurito = NULL;
	}
	else {
		// -------------------------------
		// This below commented line is recursive way.
		// -------------------------------
		//
		// decoratedBurito = input.decoratedBurito->copyobj();


		// -------------------------------
		// Use non-recursive way.
		// -------------------------------

		vector<const Burito*> buritoList =
			input.getDecoratedBurito()->getAllDecoPointer();
		vector<const Burito*>::reverse_iterator iter_begin, iter_end;
		iter_begin = buritoList.rbegin();
		iter_end = buritoList.rend();

		// ;
		Burito *prevBurito = NULL;
		try {
			for (; iter_begin != iter_end; iter_begin++) {
				const Burito *curBurito = *iter_begin;
				// FOR: all 'curBurito', type 'Burito*'.
				//   This is the reverse order of decorated burito_s.
				prevBurito = curBurito->copyobjExceptDeco(prevBurito);
			}
		} catch (const exception &e) {
			// destroy 'prevBurito', and re-throw exception.
			if (prevBurito != NULL) { delete prevBurito; }
			throw e;
		}
		decoratedBurito = prevBurito;
	}
}
Decorator::Decorator(Decorator &&input) {
	decoratedBurito = move(input.decoratedBurito);
	input.decoratedBurito = NULL;
}
Decorator& Decorator::operator=(const Decorator& input) {
	if (this == &input) { return *this; }

	if (decoratedBurito == NULL) {
		delete decoratedBurito;
		decoratedBurito = NULL;
	}

	if (input.decoratedBurito == NULL) {
		decoratedBurito = NULL;
	}
	else {
		// -------------------------------
		// This below commented line is recursive way.
		// -------------------------------
		//
		// decoratedBurito = input.decoratedBurito->copyobj();


		// -------------------------------
		// Use non-recursive way.
		// -------------------------------

		vector<const Burito*> buritoList =
			input.getDecoratedBurito()->getAllDecoPointer();
		vector<const Burito*>::reverse_iterator iter_begin, iter_end;
		iter_begin = buritoList.rbegin();
		iter_end = buritoList.rend();

		// ;
		Burito *prevBurito = NULL;
		try {
			for (; iter_begin != iter_end; iter_begin++) {
				const Burito *curBurito = *iter_begin;
				// FOR: all 'curBurito', type 'Burito*'.
				//   This is the reverse order of decorated burito_s.
				prevBurito = curBurito->copyobjExceptDeco(prevBurito);
			}
		} catch (const exception &e) {
			// destroy 'prevBurito', and re-throw exception.
			if (prevBurito != NULL) { delete prevBurito; }
			throw e;
		}
		decoratedBurito = prevBurito;
	}
	return *this;
}
Decorator& Decorator::operator=(Decorator&& input) {
	if (this == &input) { return *this; }
	swap(decoratedBurito, input.decoratedBurito);
	return *this;
}
Decorator::~Decorator() {
	if (decoratedBurito != NULL) { delete decoratedBurito; }
}
Decorator::Decorator(const Decorator &input, Burito* decoBurito) {
	decoratedBurito = decoBurito;
}



// -------------------------------
// methods
// -------------------------------

int Decorator::getCost() const {
	// NOTE: use non-recursion method.

	vector<const Burito*> buritoList = getAllDecoPointer();

	// -------------------------------
	// Make return value.
	// -------------------------------

	int ret = 0;
	if (buritoList.empty()) { return ret; }
	vector<const Burito*>::reverse_iterator iter_begin, iter_end;
	iter_begin = buritoList.rbegin();
	iter_end = buritoList.rend();

	// Sum all
	for (; iter_begin != iter_end; iter_begin++) {
		const Burito *curBurito = *iter_begin;
		// FOR: all 'curBurito', type 'Burito*'.
		ret += curBurito->getCostSelf();
	}

	return ret;
}

string Decorator::getDescription() const {
	// NOTE: use non-recursion method.

	vector<const Burito*> buritoList = getAllDecoPointer();

	// -------------------------------
	// Make return value.
	// -------------------------------

	if (buritoList.empty()) { return string(""); }
	stringstream ret;
	vector<const Burito*>::reverse_iterator iter_begin, iter_end;
	iter_begin = buritoList.rbegin();
	iter_end = buritoList.rend();

	// Add string of first one

	const Burito *curBurito = *iter_begin;
	iter_begin++;
	ret << (curBurito->getDescriptionSelf());

	// Add other string
	for (; iter_begin != iter_end; iter_begin++) {
		const Burito *curBurito = *iter_begin;
		// FOR: all 'curBurito', type 'Burito*', except the first one.
		ret << "\n+ " << (curBurito->getDescriptionSelf());
	}

	return ret.str();
}

vector<int> Decorator::getIngredientsInfo() const {
	// NOTE: use non-recursion method.

	vector<const Burito*> buritoList = getAllDecoPointer();

	// -------------------------------
	// Make return value.
	// -------------------------------

	vector<int> ret;
	if (buritoList.empty()) { return ret; }
	vector<const Burito*>::reverse_iterator iter_begin, iter_end;
	iter_begin = buritoList.rbegin();
	iter_end = buritoList.rend();

	// ;
	for (; iter_begin != iter_end; iter_begin++) {
		const Burito *curBurito = *iter_begin;
		// FOR: all 'curBurito', type 'Burito*'.
		if (curBurito->getCostSelf() < 0) {
			// CASE OF: 'combo' or 'set' burito.
			//   Should remove previous ingredient type value of
			//     'BaseBurito' or 'Drink' etc.
			ret.clear();
		}
		ret.push_back(curBurito->getIngredientInfoSelf());
	}

	return ret;
}

Burito* Decorator::getDecoratedBurito() {
	return decoratedBurito;
}

const Burito* Decorator::getDecoratedBurito() const {
	return decoratedBurito;
}

vector<Burito*> Decorator::getAllDecoPointer() {
	// -------------------------------
	// Getting all 'decoratedBurito' list.
	// -------------------------------

	Burito* curBurito = this;
	vector<Burito*> buritoList;

	while (curBurito) {
		buritoList.push_back(curBurito);
		curBurito = curBurito->getDecoratedBurito();
	}

	return buritoList;
}

vector<const Burito*> Decorator::getAllDecoPointer() const {
	// -------------------------------
	// Getting all 'decoratedBurito' list.
	// -------------------------------

	const Burito* curBurito = this;
	vector<const Burito*> buritoList;

	while (curBurito) {
		buritoList.push_back(curBurito);
		curBurito = curBurito->getDecoratedBurito();
	}

	return buritoList;
}

//EOF

