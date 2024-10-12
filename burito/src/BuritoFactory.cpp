
#include "BuritoFactory.h"

#include <stdexcept>
#include <sstream>

using namespace std;

Burito* BuritoFactory::makeOrderedMenu(int type) {
	Burito *ordered = new BaseBurito();

	try {
		switch (type) {
			// 단품.
			case 1:
				return ordered;
				break;
			// 콤보
			case 2:
				ordered = new Drink(ordered);
				ordered = new ComboDiscount(ordered);
				return ordered;
				break;
			// 세트.
			case 3:
				ordered = new Drink(ordered);
				ordered = new Fries(ordered);
				ordered = new SetDiscount(ordered);
				return ordered;
				break;
			// wrong value.
			default:
				delete ordered;
				return NULL;
				break;
		}
	} catch (const exception &e) {
		// destroy 'ordered', and re-throw exception.
		delete ordered;
		throw e;
	}

	return NULL;
}



Burito* BuritoFactory::makeOrderedMenu(Burito* burito, int ingredientType) {
	switch (ingredientType) {
		// 점보.
		case 1:
			burito = new Jumbo(burito);
			break;
		// 소세지.
		case 2:
			burito = new Sausage(burito);
			break;
		// 음료수.
		case 3:
			burito = new Drink(burito);
			break;
		// 감튀.
		case 4:
			burito = new Fries(burito);
			break;
		// wrong value.
		default:
			return NULL;
			break;
	}
	return burito;
}



Burito* BuritoFactory::makeOrderedMenu(const vector<int> &ingredientsInfo) {
	if (ingredientsInfo.size() == (size_t)0) {
		// CASE OF: there is no type value at all.
		return NULL;
	}

	// setting up iterator

	vector<int>::const_iterator iter_begin, iter_end;
	iter_begin = ingredientsInfo.begin();
	iter_end = ingredientsInfo.end();

	// Get 'Burito*', for base order (단품, 콤보, etc).

	Burito *ordered = makeOrderedMenu(*iter_begin);
	if (ordered == NULL) {
		// CASE OF: wrong value.
		return NULL;
	}
	iter_begin++;

	// LOOP: ingredientsInfo type loop, except the first one.
	for (; iter_begin != iter_end; iter_begin++) {
		// get ingredient type.


		int ingredientType = *iter_begin;
		try {
			Burito *newBurito = BuritoFactory::makeOrderedMenu(
					ordered, ingredientType);
			if (newBurito == NULL) {
				// CASE OF: wrong value.
				delete ordered;
				return NULL;
			}
			else {
				// CASE OF: not wrong value ('newBurito' has 'ordered' pointer).
				ordered = newBurito;
			}
		} catch (const exception &e) {
			// destroy 'ordered', and re-throw exception.
			delete ordered;
			throw e;
		}
	}
	// END_LOOP: ingredientsInfo type loop, except the first one.

	return ordered;
}



string BuritoFactory::makeLineDescription(const vector<int> &ingredientsInfo) {
	if (ingredientsInfo.size() == (size_t)0) {
		// CASE OF: there is no type value at all.
		return string("");
	}
	stringstream ret;

	// setting up iterator

	vector<int>::const_iterator iter_begin, iter_end;
	iter_begin = ingredientsInfo.begin();
	iter_end = ingredientsInfo.end();

	// For base order (단품, 콤보, etc).
	switch (*iter_begin) {
		// 단품.
		case 1:
			ret << "단품";
			break;
		// 콤보
		case 2:
			ret << "콤보";
			break;
		// 세트.
		case 3:
			ret << "세트";
			break;
		// wrong value.
		default:
			return string("");
			break;
	}
	iter_begin++;

	// LOOP: ingredientsInfo type loop, except the first one.
	for (; iter_begin != iter_end; iter_begin++) {
		// get ingredient type.
		int ingredientType = *iter_begin;

		switch (ingredientType) {
			// 점보.
			case 1:
				ret << " + 점보";
				break;
			// 소세지.
			case 2:
				ret << " + 소세지";
				break;
			// 음료수.
			case 3:
				ret << " + 음료수";
				break;
			// 감튀.
			case 4:
				ret << " + 감자튀김";
				break;
			// wrong value.
			default:
				return string("");
				break;
		}
	}
	// END_LOOP: ingredientsInfo type loop, except the first one.

	return ret.str();
}


//EOF

