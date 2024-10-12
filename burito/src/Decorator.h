
#pragma once

#include "Burito.h"

// -------------------------------
// class 'Decorator', extends 'Burito'.
// This class is for decorator design pattern.
// -------------------------------
class Decorator : public Burito
{
public:

	// -------------------------------
	// constructor, assign operator, etc.
	// -------------------------------

	// Construct using decorated parent object.
	// Param 'decoBurito',
	//   should be the pointer from the 'new' operator,
	//   or NULL.
	Decorator(Burito* decoBurito);
	Decorator();
	Decorator(const Decorator &input);
	Decorator(Decorator &&input);
	virtual Decorator& operator=(const Decorator& input);
	virtual Decorator& operator=(Decorator&& input);
	virtual ~Decorator();
	// Call copy constructor, with self instance, using 'new' operator.
	virtual Burito* copyobj() const = 0;
protected:
	// Copy constructor but use specific decorated parent object.
	// Param 'decoBurito',
	//   should be the pointer from the 'new' operator,
	//   or NULL.
	Decorator(const Decorator &input, Burito* decoBurito);
public:
	// Call constructor,
	//   with self instance and 'decoBurito' param, using 'new' operator.
	// This will ignore 'decoBurito' param,
	//   if this class 'type' does not have decorated parent class at all.
	// This function is for making non-recursive call possible,
	//   while copying object.
	virtual Burito* copyobjExceptDeco(Burito* decoBurito) const = 0;


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
	virtual int getCostSelf() const = 0;
	// Get string description of burito.
	virtual std::string getDescription() const;
	// Get string description of burito, for current class only.
	virtual std::string getDescriptionSelf() const = 0;
	// Get ingredientsInfo(vector<int>) from burito.
	virtual std::vector<int> getIngredientsInfo() const;
	// Get ingredientInfo, for current class only
	virtual int getIngredientInfoSelf() const = 0;

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



	// -------------------------------
	// fields
	// -------------------------------

protected:

	// pointer of parent, for decorator design pattern.
	Burito* decoratedBurito;
};

//EOF
