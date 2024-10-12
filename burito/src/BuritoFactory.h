#pragma once

#include "BaseBurito.h"
#include "Drink.h"
#include "Fries.h"
#include "ComboDiscount.h"
#include "SetDiscount.h"
#include "Sausage.h"
#include "Jumbo.h"

#include <vector>

class BuritoFactory
{
public:
	BuritoFactory() { ; }
	~BuritoFactory() { ; }

	// Make base 'Burito*', factory method.
	// Returns NULL if value is wrong.
	// Program must use 'delete' for returned pointer value.
	static Burito* makeOrderedMenu(int type);
	// Make 'Burito', with added ingredient, factory method.
	// Returns NULL if the value is wrong.
	// Param 'burito' should be the pointer value from 'new' operator.
	// When return value is not NULL,
	//   do not use 'delete' manually for original 'burito' param,
	//   instead use 'delete' for returned pointer value.
	// When return value is NULL, or if this function throws exception,
	//   original 'burito' of param will remain,
	//   need to manually use 'delete' for dynamic allocation.
	static Burito* makeOrderedMenu(Burito* burito, int ingredientType);
	// Make full 'Burito*', factory method.
	// This use 'vector<int>' for one type value and many ingredients value.
	// Returns NULL if the value is wrong.
	// Program must use 'delete' for returned pointer value.
	static Burito* makeOrderedMenu(const std::vector<int> &ingredientsInfo);

	// Make line description string using 'vector<int>'.
	// This use 'vector<int>' for one type value and many ingredients value.
	// Returns empty string if the value is wrong.
	static std::string makeLineDescription(const std::vector<int> &ingredientsInfo);
};

//EOF
