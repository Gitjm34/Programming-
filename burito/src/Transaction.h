#pragma once

#include <vector>
#include "Burito.h"

// -------------------------------
// class 'Transaction'.
// Holds one order ("Burito*" type),
//   and other information.
// -------------------------------
class Transaction
{
public:

	// -------------------------------
	// constructor, assign operator, etc.
	// -------------------------------
	Transaction(int orderID);
	Transaction(const Transaction &input);
	Transaction(Transaction &&input);
	virtual Transaction& operator=(
			const Transaction& input
			);
	virtual Transaction& operator=(
			Transaction&& input
			);
	virtual ~Transaction();
	// Call copy constructor, with self instance, using 'new' operator.
	virtual Transaction* copyobj() const;


	// -------------------------------
	// methods
	// -------------------------------

public:

	// ;
	virtual int getOrderID() const {
		return orderID;
	}
	// ;
	virtual const std::vector<int>& getIngredientsInfo() const {
		return ingredientsInfo;
	}
	// ;
	virtual const Burito* getOrderedMenu() const {
		return orderedMenu;
	}
	// Set 'orderedMenu', and set 'ingredientsInfo' too.
	// after this, 'delete' operation for 'orderedmenu' param,
	//   will be executed at this object's destroyer,
	//   even if this function throws exception like memory allocation error.
	virtual void setOrderedMenu(Burito *orderedMenu);
	// Set 'ingredientsInfo, and 'orderedMenu' too (re-allocate).
	// If one of the type value of 'ingredientsInfo' is wrong,
	//   'orderedMenu' will be NULL,
	//   and return value will be 1.
	// Return 0 if success.
	virtual int setIngredientsInfo(const std::vector<int> &ingredientsInfo);
	// Set 'ingredientsInfo, and 'orderedMenu' too (re-allocate).
	// If one of the type value of 'ingredientsInfo' is wrong,
	//   'orderedMenu' will be NULL,
	//   and return value will be 1.
	// Return 0 if success.
	virtual int setIngredientsInfo(std::vector<int> &&ingredientsInfo);
protected:
	// Re-allocated 'orderedMenu', using 'ingredientsInfo'.
	// If one of the type value of 'ingredientsInfo' is wrong,
	//   'orderedMenu' will be NULL,
	//   and return value will be 1.
	// Return 0 if success.
	virtual int remakeOrderedMenu();


	// -------------------------------
	// fields
	// -------------------------------

private:
	int orderID;
	std::vector<int> ingredientsInfo;
	Burito* orderedMenu;
};

//EOF
