#pragma once

#include <string>
#include <vector>

// -------------------------------
// class 'Burito'.
// This is the actual base class,
//   for decorater design pattern.
// -------------------------------
class Burito
{
public:

	// -------------------------------
	// constructor, assign operator, etc.
	// -------------------------------

	// Burito() { ; }
	// Burito(const Burito &input) { ; }
	// Burito(Burito &&input) { ; }
	// virtual Burito& operator=(const Burito& input) { ; }
	// virtual Burito& operator=(Burito&& input) { ; }
	virtual ~Burito() { ; }
	// Call copy constructor, with self instance, using 'new' operator.
	virtual Burito* copyobj() const = 0;
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
	virtual int getCost() const = 0;
	// Get cost of burito, for current class only.
	virtual int getCostSelf() const = 0;
	// Get string description of burito.
	virtual std::string getDescription() const = 0;
	// Get string description of burito, for current class only.
	virtual std::string getDescriptionSelf() const = 0;
	// Get ingredientsInfo(vector<int>) from burito.
	virtual std::vector<int> getIngredientsInfo() const = 0;
	// Get ingredientInfo, for current class only
	virtual int getIngredientInfoSelf() const = 0;

	// This function returns 'decoratedBurito' (pointer of parent).
	// This function makes non-recursive call possible,
	//   for decorator design pattern.
	virtual Burito* getDecoratedBurito() = 0;
	// This function returns 'decoratedBurito' (pointer of parent).
	// This function makes non-recursive call possible,
	//   for decorator design pattern.
	virtual const Burito* getDecoratedBurito() const = 0;

	// This function returns all 'decoratedBurito' (pointer of parent),
	//   include pointer of current class instance.
	// Outer decorated instance will be the first one of the returned list.
	// This function makes non-recursive call possible,
	//   for decorator design pattern.
	virtual std::vector<Burito*> getAllDecoPointer() = 0;
	// This function returns all 'decoratedBurito' (pointer of parent),
	//   include pointer of current class instance.
	// Outer decorated instance will be the first one of the returned list.
	// This function makes non-recursive call possible,
	//   for decorator design pattern.
	virtual std::vector<const Burito*> getAllDecoPointer() const  = 0;

};

//EOF
