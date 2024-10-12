
#pragma once

#include "Decorator.h"

// -------------------------------
// class 'Fries', extends 'Decorator'.
// This class is for decorator design pattern.
// -------------------------------
class Fries : public Decorator
{
public:

	// -------------------------------
	// constructor, assign operator, etc.
	// -------------------------------

	// Construct using decorated parent object.
	// Param 'decoBurito',
	//   should be the pointer from the 'new' operator,
	//   or NULL.
	Fries(Burito* decoBurito);
	Fries();
	Fries(const Fries &input);
	Fries(Fries &&input);
	virtual Fries& operator=(const Fries& input);
	virtual Fries& operator=(Fries&& input);
	virtual ~Fries();
	virtual Burito* copyobj() const;
protected:
	// Copy constructor but use specific decorated parent object.
	// Param 'decoBurito',
	//   should be the pointer from the 'new' operator,
	//   or NULL.
	Fries(const Fries &input, Burito* decoBurito);
public:
	// Call constructor,
	//   with self instance and 'decoBurito' param, using 'new' operator.
	// This will ignore 'decoBurito' param,
	//   if this class 'type' does not have decorated parent class at all.
	// This function is for making non-recursive call possible,
	//   while copying object.
	virtual Burito* copyobjExceptDeco(Burito* decoBurito) const;


	// -------------------------------
	// methods
	// -------------------------------

public:

	// NOTE:
	// 'Self' version makes non-recursive call possible,
	//   for decorator design pattern.

	// Get cost of burito, for current class only.
	virtual int getCostSelf() const;
	// Get string description of burito, for current class only.
	virtual std::string getDescriptionSelf() const;
	// Get ingredientInfo, for current class only
	virtual int getIngredientInfoSelf() const;

};

//EOF
