#pragma once

#include "Transaction.h"

#include <vector>

// -------------------------------
// class 'TransactionManager'.
// Holds list of 'Transaction' ("vector<Transaction>").
// -------------------------------
class TransactionManager
{
public:

	// -------------------------------
	// constructor, assign operator, etc.
	// -------------------------------
	TransactionManager();
	TransactionManager(const TransactionManager &input);
	TransactionManager(TransactionManager &&input);
	virtual TransactionManager& operator=(
			const TransactionManager& input
			);
	virtual TransactionManager& operator=(
			TransactionManager&& input
			);
	virtual ~TransactionManager();
	// Call copy constructor, with self instance, using 'new' operator.
	virtual TransactionManager* copyobj() const;


	// -------------------------------
	// methods
	// -------------------------------

	// ;
	virtual bool isEmpty() const;
	// Add Transaction, using the pointer of 'Burito'.
	// Param 'burito' should be valid (not NULL),
	//   and should be the value of pointer using 'new' operator.
	// After this, 'delete' operation for 'burito' param,
	//   will be executed at this function or TransactionManager (tm),
	//   even if this function throws an Exception.
	// If 'saveToFile' is true,
	//   this will call 'TransactionManager::writeTransaction'.
	//   Do not set this 'true' when reading Transactions from file.
	void addTransactionFromBurito(Burito* burito, bool saveToFile);
	// Add Transaction, from 'Ingredients' list.
	// 'Ingredients' list use 'vector<int>',
	//   for one type value and many ingredients value.
	// If one of the type value of 'ingrInfo' is wrong,
	//   return value will be 1,
	//   and Transaction will not be added.
	// Return 0 if success.
	// If 'saveToFile' is true,
	//   this will call 'TransactionManager::writeTransaction'.
	//   Do not set this 'true' when reading Transactions from file.
	int addTransactionFromIngrInfo(
			const std::vector<int> &ingrInfo, bool saveToFile);
	// Add 'newTransaction'.
	// After this, program should not access '*newTransaction',
	//   because this function call 'std::move(*newTransaction)',
	//   to add 'Transaction' type object at 'vector<Transaction>' type.
	virtual void addTransaction(Transaction* newTransaction);
	// This function will print result to 'stdout'.
	virtual void processFrontTransaction();
	// This function will print result to 'stdout'.
	virtual void printTransaction() const;
	// Delete Transaction, with index, starts with 0.
	// This function will print result to 'stdout'.
	virtual void deleteTransaction(int index);

	virtual void readTransaction();
	virtual void writeTransaction() const;


	// -------------------------------
	// fields
	// -------------------------------

private:
	std::vector<Transaction> orderTransactions;
	// order ID count, for application.
	int globalOrderID;
};

//EOF
