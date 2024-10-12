#pragma once

#include "BuritoFactory.h"
#include "TransactionManager.h"

class App
{
public:
	App();
	virtual ~App();

	void run();


	// -------------------------------
	// enum classes
	// -------------------------------

	// enum class MenuV.
	// User interacation value of top menu.
	enum class MenuV {
		ADD, // Add Transaction
		CANCEL, // Cancel Transaction
		PRT, // Process Transaction
		EXIT, // Exit program
		INVALID, // invalid input
	};


	// -------------------------------
	// methods
	// -------------------------------

private:
	// Read user interaction value of top menu.
	MenuV processTopMenu() const;
	// Read user interaction value of base burito menu.
	int processBaseBuritoMenu() const;
	// Read user interaction value of ingredients menu.
	int processIngredientsMenu() const;
	// Read user interaction value of cancel menu.
	// Return value will be the index for calcel transaction, starts with 1.
	int processCancelMenu() const;

	// Add Transaction, with user interaction.
	void addTransaction();
	// Process front Transaction.
	void processFrontTransaction();
	// Cancel Transaction, with user interaction.
	void cancelTransaction();

	// Print all Transaction list.
	void printTransaction() const;
	// Load Transactions from file.
	void readTransaction();
	// Save Transactions to file.
	void writeTransaction() const;


	// -------------------------------
	// fields
	// -------------------------------

private:
	BuritoFactory* bf;
	TransactionManager* tm;

};

//EOF
