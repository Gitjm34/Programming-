
#pragma once

#include "Burito.h"

// -------------------------------
// class 'BaseBurito', extends 'Burito'.
// This is not actual base class,
//   'base' means the base of 'food'.
// -------------------------------
class BaseBurito : public Burito
{
public:

	// -------------------------------
	// constructor, assign operator, etc.
	// -------------------------------
	BaseBurito() { ; }
	BaseBurito(const BaseBurito &input) { ; }
	BaseBurito(BaseBurito &&input) { ; }
	virtual BaseBurito& operator=(const BaseBurito& input) { return *this; }
	virtual BaseBurito& operator=(BaseBurito&& input) { return *this; }
	virtual ~BaseBurito() { ; }
	// Call copy constructor, with self instance, using 'new' operator.
	virtual Burito* copyobj() const {
		return new BaseBurito(*this);
	}
public:
	// Call constructor,
	//   with self instance and 'decoBurito' param, using 'new' operator.
	// This will ignore 'decoBurito' param,
	//   if this class 'type' does not have decorated parent class at all.
	// This function is for making non-recursive call possible,
	//   while copying object.
	virtual Burito* copyobjExceptDeco(Burito* decoBurito) const {
		return new BaseBurito(*this);
	}


	// -------------------------------
	// methods
	// -------------------------------

public:

	// NOTE:
	// 'Self' version makes non-recursive call possible,
	//   for decorator design pattern.

	// Get cost of burito.
	virtual int getCost() const;
	// Get cost of burito, for current class only.
	virtual int getCostSelf() const;
	// Get string description of burito.
	virtual std::string getDescription() const;
	// Get string description of burito, for current class only.
	virtual std::string getDescriptionSelf() const;
	// Get ingredientsInfo(vector<int>) from burito.
	virtual std::vector<int> getIngredientsInfo() const;
	// Get ingredientInfo, for current class only
	virtual int getIngredientInfoSelf() const;

	// This function returns 'decoratedBurito' (pointer of parent).
	// This function makes non-recursive call possible,
	//   for decorator design pattern.
	virtual Burito* getDecoratedBurito();
	// This function returns 'decoratedBurito' (pointer of parent).
	// This function makes non-recursive call possible,
	//   for decorator design pattern.
	virtual const Burito* getDecoratedBurito() const;

	// This function returns all 'decoratedBurito' (pointer of parent),
	//   include pointer of current class instance.
	// Outer decorated instance will be the first one of the returned list.
	// This function makes non-recursive call possible,
	//   for decorator design pattern.
	virtual std::vector<Burito*> getAllDecoPointer();
	// This function returns all 'decoratedBurito' (pointer of parent),
	//   include pointer of current class instance.
	// Outer decorated instance will be the first one of the returned list.
	// This function makes non-recursive call possible,
	//   for decorator design pattern.
	virtual std::vector<const Burito*> getAllDecoPointer() const;
};

//EOF
