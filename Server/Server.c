/*
 ============================================================================
 Name        : server.c
 Author      : Belal
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "server.h"


uint8_t static seqNum = 0;

/*
 * 1. Create a global array of ST_accountsDB_t for the valid accounts database
 * 1. Fill in the array initially with any valid data
 * 1. This array has a maximum of 255 element/account data
 */
ST_accountsDB_t validAccounts[ACCOUNTS] = {
		{10000, RUNNING, "1000000000000000001"},
		{20000, RUNNING, "1000000000000000002"},
		{30000, BLOCKED, "1000000000000000003"},
		{40000, BLOCKED, "1000000000000000004"},
		{50000, RUNNING, "1000000000000000005"},
		{60000, BLOCKED, "1000000000000000006"},
		/*{balance,STATE ,          PAN         }*/
		/*{float  ,      ,    19 char + '\0'    }*/
};

/*
 * Create a global array of ST_transaction_t
 * 1. Fill in the array initially with 0s.
 * 2. This array has a maximum of 255 element/transaction data
 */
ST_transaction_t transactions[ACCOUNTS] =
{
		{
				{//cardHolderData
						"Belal Mohamed",
						"12/22"
						"1000000000000000001",
				},
				{//terminalData
						500,
						1000,
						"25/06/2022"
				}
		}
};

uint8_t accountIndex;


/*
 * 1. This function will take all transaction data and validate its data.
 * 2. It checks the account details and amount availability.
 * 3. If the account does not exist return FRAUD_CARD,
 *    if the amount is not available will return DECLINED_INSUFFECIENT_FUND,
 *    if the account is blocked will return DECLINED_STOLEN_CARD,
 *    if a transaction can't be saved will return INTERNAL_SERVER_ERROR
 *    and will not save the transaction,
 *    else returns APPROVED.
 * 4. It will update the database with the new balance.
 */
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	if (isValidAccount(&transData->cardHolderData) == OK_FROM_SERVER) {
		if (isBlockedAccount(&validAccounts[accountIndex]) == OK_FROM_SERVER) {

			printf(" Your Balance is Before Transaction: %f \n \n", validAccounts[accountIndex].balance);
			if (isAmountAvailable(&transData->terminalData) == OK_FROM_SERVER) {
				transData->transState = APPROVED;
				if (saveTransaction(transData) == OK_FROM_SERVER) {
					validAccounts[accountIndex].balance -= transData->terminalData.transAmount;
					Balance = validAccounts[accountIndex].balance;
					//saveTransaction(transData);

					printf("\n");
					printf("Transaction  Saved :)\n");
					printf("Transaction  Sequence number is %d\n", seqNum);
					printf("\n");
					return APPROVED;
				}
				else {
					transData->transState = INTERNAL_SERVER_ERROR;
					printf("\n");
					printf("Transaction  Saved :)\n");
					printf("Transaction  Sequence number is %d\n", seqNum);
					printf("\n");
					return INTERNAL_SERVER_ERROR;
				}
			}
			else {
				transData->transState = DECLINED_INSUFFECIENT_FUND;
				saveTransaction(transData);
				printf("\n");
				printf("Transaction  Saved :)\n");
				printf("Transaction  Sequence number is %d\n", seqNum);
				printf("\n");
				return DECLINED_INSUFFECIENT_FUND;
			}
		}
		else {
			transData->transState = DECLINED_STOLEN_CARD;
			saveTransaction(transData);
			printf("\n");
			printf("Transaction  Saved :)\n");
			printf("Transaction  Sequence number is %d\n", seqNum);
			printf("\n");
			return DECLINED_STOLEN_CARD;
		}
	}
	else {
		transData->transState = FRAUD_CARD;
		saveTransaction(transData);
		printf("\n");
		printf("Transaction  Saved :)\n");
		printf("Transaction  Sequence number is %d\n", seqNum);
		printf("\n");
		return FRAUD_CARD;
	}
}

/*
 * 1. This function will take card data and validate these data.
 * 2. It checks if the PAN exists or not in the server's database.
 * 3. If the PAN doesn't exist will return ACCOUNT_NOT_FOUND,
 *    else will return OK
 */
EN_serverError_t isValidAccount(const ST_cardData_t* cardData) {
	for (int i = 0; i < ACCOUNTS - 1; ++i) {
		if (!strcmp(validAccounts[i].primaryAccountNumber, cardData->primaryAccountNumber)) {
			accountIndex = i; // IMPORTANT

			return OK_FROM_SERVER;
		}
	}
	return ACCOUNT_NOT_FOUND;
}


/*
 * 1. This function will take a reference to an existing account in the database.
 * 2. It checks if the account is blocked or not.
 * 3. If the account is blocked, will return BLOCKED_ACCOUNT,
 *    else will return SERVER_OK.
 */
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	if (accountRefrence->state == RUNNING) {
		return OK_FROM_SERVER;
	}
	return BLOCKED_ACCOUNT;
}

/*
 * 1. This function will take terminal data and validate these data.
 * 2. It checks if the transaction's amount is available or not.
 * 3. If the transaction amount is greater than the balance in the database
 *    will return LOW_BALANCE, else will return OK
 */
EN_serverError_t isAmountAvailable(const ST_terminalData_t* termData) {
	if (validAccounts[accountIndex].balance >= termData->transAmount) {
		Balance = validAccounts[accountIndex].balance;
		return OK_FROM_SERVER;
	}
	else {
		return LOW_BALANCE;
	}
}


/*
 * 1. This function will store all transaction data in the transactions database.
 * 2. It gives a sequence number to a transaction,
 *    this number is incremented once a transaction is processed into the server,
 *    you must check the last sequence number in the server to give
 *    the new transaction a new sequence number.
 * 3. It saves any type of transactions, APPROVED or DECLINED,
 *    with the specific reason for declining/transaction state.
 * 4. If the transaction can't be saved, for any reason
 *    (ex: dropped connection) will return SAVING_FAILED,
 *    else will return SERVER_OK, you can simulate this
 *    by commenting on the lines you where your code writes
 *    the transaction data in the database.
 * 5. It checks if the transaction is saved or not using the getTransaction function.
 */
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	if (seqNum >= ACCOUNTS) {
		return SAVING_FAILED;
	}
	///////////////////////// cardHolderData //////////////////////////
	strcpy_s(transactions[seqNum].cardHolderData.cardHolderName, \
		NAME_MAX_SIZE, \
		transData->cardHolderData.cardHolderName);

	strcpy_s(transactions[seqNum].cardHolderData.cardExpirationDate, \
		EXPIRY_DATE_SIZE + 1, \
		transData->cardHolderData.cardExpirationDate);

	strcpy_s(transactions[seqNum].cardHolderData.primaryAccountNumber, \
		PAN_MAX_SIZE, \
		transData->cardHolderData.primaryAccountNumber);
	/////////////////////////////////////////////////////////////////////


	/////////////////////////// terminalData ////////////////////////////
	strcpy_s(transactions[seqNum].terminalData.transactionDate, \
		(Trans_DATE_SIZE + 2), \
		transData->terminalData.transactionDate);

	transactions[seqNum].terminalData.transAmount = transData->terminalData.transAmount;
	/////////////////////////////////////////////////////////////////////


	transactions[seqNum].transactionSequenceNumber = seqNum;
	transactions[seqNum].transState = transData->transState;

	seqNum++;


	return OK_FROM_SERVER;
}

/*
 * 1. This function will take a transaction sequence number
 *    and search for this transaction in the database.
 * 2. If the transaction can't be found will return TRANSACTION_NOT_FOUND,
 *    else will return OK and store the transaction in a structure
 */
EN_serverError_t getTransaction(const uint32_t transactionSequenceNumber, const ST_transaction_t* transData) {

	if (transactionSequenceNumber <= seqNum) {

		printf("Transaction details:-\n");
		printf("\n");
		printf("Name: %s \n", transactions[transactionSequenceNumber].cardHolderData.cardHolderName);
		printf("Primary Account Number: %s \n", transactions[transactionSequenceNumber].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s \n", transactions[transactionSequenceNumber].cardHolderData.cardExpirationDate);
		printf("\n");
		printf("Transaction Date: %s \n", transactions[transactionSequenceNumber].terminalData.transactionDate);
		printf("Transaction Amount: %f \n", transactions[transactionSequenceNumber].terminalData.transAmount);
		printf("Max Transaction Amount: %f \n", transactions[transactionSequenceNumber].terminalData.maxTransAmount);
		printf("\n");
		if (transactions[transactionSequenceNumber].transState == APPROVED) {
			printf("Status of The Transaction: APPROVED \n");
		}
		else if (transactions[transactionSequenceNumber].transState == DECLINED_INSUFFECIENT_FUND) {
			printf("Status of The Transaction: DECLINED INSUFFECIENT FUND \n");
		}
		else if (transactions[transactionSequenceNumber].transState == DECLINED_STOLEN_CARD) {
			printf("Status of The Transaction: DECLINED STOLEN CARD \n");
		}
		else if (transactions[transactionSequenceNumber].transState == FRAUD_CARD) {
			printf("Status of The Transaction: FRAUD CARD \n");
		}
		else if (transactions[transactionSequenceNumber].transState == INTERNAL_SERVER_ERROR) {
			printf("Status of The Transaction: INTERNAL SERVER ERROR \n");
		}
		printf("\n");
		return OK_FROM_SERVER;
	}

	return TRANSACTION_NOT_FOUND;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 1
void recieveTransactionDataTest(void) {
	ST_transaction_t transaction;

	printf(" \n");
	printf("Tester Name : Belal \n");
	printf("Function Name : recieveTransactionDataTest \n");
	printf(" \n");
	printf("Correct input : 1000000000000000001 >>> Running \n");
	printf(" \n");

	if (getCardHolderName(&transaction.cardHolderData) != OK) {
		printf(" WRONG_NAME \n");
	}
	if (getCardExpiryDate(&transaction.cardHolderData) != OK) {
		printf(" WRONG_EXP_DATE \n");
	}
	if (getTransactionDate(&transaction.terminalData) != OK) {
		printf(" WRONG_DATE \n");
	}
	if (isCardExpired(&transaction.cardHolderData, &transaction.terminalData) != OK) {
		printf(" WRONG_DATE \n");
	}

	if (getCardPAN(&transaction.cardHolderData) != OK) {
		printf(" WRONG_PAN \n");
	}
	if (setMaxAmount(&transaction.terminalData) != OK_FROM_TERMINAL) {
		printf(" INVALID_MAX_AMOUNT \n");
		return;
	}
	if (getTransactionAmount(&transaction.terminalData) != OK) {
		printf(" WRONG_PAN \n");
	}
	if (isBelowMaxAmount(&transaction.terminalData) != OK_FROM_SERVER) {
		printf(" EXCEED_MAX_AMOUNT \n");
		return 0;
	}
	


	if (recieveTransactionData(&transaction) == OK_FROM_SERVER) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : ACCEPTED\n");
		return 0;
	}
	else if (recieveTransactionData(&transaction) == INTERNAL_SERVER_ERROR) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<INTERNAL_SERVER_ERROR>>>>>>\n");
		return 0;
	}
	else if (recieveTransactionData(&transaction) == FRAUD_CARD) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<FRAUD_CARD>>>>>>\n");
		return 0;
	}
	else if (recieveTransactionData(&transaction) == DECLINED_STOLEN_CARD) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<DECLINED_STOLEN_CARD>>>>>>\n");
		return 0;
	}
	else if (recieveTransactionData(&transaction) == DECLINED_INSUFFECIENT_FUND) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<DECLINED_INSUFFECIENT_FUND>>>>>>\n");
		return 0;
	}
}

// 2
void isValidAccountTest(void) {
	ST_transaction_t transaction;

	printf(" \n");
	printf("Tester Name : Belal \n");
	printf("Function Name : isValidAccountTest \n");
	printf(" \n");
	printf(" \n");
	if (getCardPAN(&transaction.cardHolderData) != OK) {
		printf(" WRONG_PAN \n");
	}
	

	if (isValidAccount(&transaction) == OK_FROM_SERVER) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : ACCEPTED\n");
		return 0;
	}
	else {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<ACCOUNT_NOT_FOUND>>>>>>\n");
		return 0;
	}
}

// 3
void isBlockedAccountTest(void) {

	ST_transaction_t transaction;
	printf(" \n");
	printf("Tester Name : Belal \n");
	printf("Function Name : isBlockedAccountTest \n");
	printf(" \n");
	printf("Correct input : 1000000000000000001 >>> Running \n");
	printf("Correct input : 1000000000000000003 >>> Blocked\n");
	printf(" \n");
	if (getCardPAN(&transaction.cardHolderData) != OK_FROM_TERMINAL) {
		printf(" WRONG_PAN \n");
		return 0;
	}
	if (isValidAccount(&transaction.cardHolderData) != OK_FROM_SERVER) {
		printf(" ACCOUNT_NOT_FOUND \n");
		return 0;
	}
	if (isBlockedAccount(&validAccounts[accountIndex]) == OK_FROM_SERVER) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : ACCEPTED\n");
		return 0;
	}
	else {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<BLOCKED_ACCOUNT>>>>>>\n");
		return 0;
	}
}


// 4
void isAmountAvailableTest(void) {

	ST_transaction_t transaction;
	printf(" \n");
	printf("Tester Name : Belal \n");
	printf("Function Name : isAmountAvailableTest \n");
	printf(" \n");
	printf("Correct input : 1000000000000000001 >>> Running \n");
	printf(" \n");
	if (getCardPAN(&transaction.cardHolderData) != OK) {
		printf(" WRONG_PAN \n");
		return 0;
	}
	if (getTransactionAmount(&transaction.terminalData) != OK) {
		printf(" WRONG_PAN \n");
		return 0;
	}
	if (isValidAccount(&transaction.cardHolderData) != OK_FROM_SERVER) {
		printf(" ACCOUNT_NOT_FOUND \n");
		return 0;
	}

	if (isAmountAvailable(&transaction.terminalData) == OK_FROM_SERVER) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : ACCEPTED\n");
		return 0;
	}
	else {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<LOW_BALANCE>>>>>>\n");
		return 0;
	}
}

// 5
void saveTransactionTest(void) {
	ST_transaction_t transaction;

	printf(" \n");
	printf("Tester Name : Belal \n");
	printf("Function Name : saveTransactionTest \n");
	printf(" \n");
	printf("Correct input : 1000000000000000001 >>> Running \n");
	printf(" \n");
	if (getCardHolderName(&transaction.cardHolderData) != OK) {
		printf(" WRONG_NAME \n");
		return 0;
	}
	if (getCardExpiryDate(&transaction.cardHolderData) != OK) {
		printf(" WRONG_EXP_DATE \n");
		return 0;
	}
	if (getTransactionDate(&transaction.terminalData) != OK) {
		printf(" WRONG_DATE \n");
		return 0;
	}
	if (isCardExpired(&transaction.cardHolderData, &transaction.terminalData) != OK) {
		printf(" WRONG_DATE \n");
		return 0;
	}

	if (getCardPAN(&transaction.cardHolderData) != OK) {
		printf(" WRONG_PAN \n");
		return 0;
	}

	if (setMaxAmount(&transaction.terminalData) != OK_FROM_TERMINAL) {
		printf(" INVALID_MAX_AMOUNT \n");
		return 0;
	}
	if (getTransactionAmount(&transaction.terminalData) != OK) {
		printf(" WRONG_PAN \n");
		return 0;
	}
	if (isBelowMaxAmount(&transaction.terminalData) != OK_FROM_SERVER) {
		printf(" WRONG_PAN \n");
		return 0;
	}


	if (isValidAccount(&transaction.cardHolderData) == OK_FROM_SERVER) {
		if (isBlockedAccount(&validAccounts[accountIndex]) == OK_FROM_SERVER) {

			printf(" Your Balance is Before Transaction: %f \n \n", validAccounts[accountIndex].balance);
			if (isAmountAvailable(&transaction.terminalData) == OK_FROM_SERVER) {
				transaction.transState = APPROVED;
				if (saveTransaction(&transaction) == OK_FROM_SERVER) {
					validAccounts[accountIndex].balance -= transaction.terminalData.transAmount;
					Balance = validAccounts[accountIndex].balance;
					//saveTransaction(transData);
					//return APPROVED;

					printf("Expected Result :  ACCEPTED\n");
					printf("Actual Result : <<<<APPROVED>>>> [ACCEPTED]\n");
					printf("Transaction  Sequence number is %d\n", seqNum);
					return 0;
				}
				else {
					transaction.transState = INTERNAL_SERVER_ERROR;
					printf("Expected Result :  ACCEPTED\n");
					printf("Actual Result : <<<<<<INTERNAL_SERVER_ERROR>>>>>>\n");
					printf("Transaction  Sequence number is %d\n", seqNum);
					return 0;
				}
			}
			else {
				transaction.transState = DECLINED_INSUFFECIENT_FUND;
				saveTransaction(&transaction);
				printf("Expected Result :  ACCEPTED\n");
				printf("Actual Result : <<<<<<DECLINED_INSUFFECIENT_FUND>>>>>>\n");
				printf("Transaction  Sequence number is %d\n", seqNum);
				return 0;
			}
		}
		else {
			transaction.transState = DECLINED_STOLEN_CARD;
			saveTransaction(&transaction);
			printf("Expected Result :  ACCEPTED\n");
			printf("Actual Result : <<<<<<DECLINED_STOLEN_CARD>>>>>>\n");
			printf("Transaction  Sequence number is %d\n", seqNum);
			return 0;
		}
	}
	else {
		transaction.transState = FRAUD_CARD;
		saveTransaction(&transaction);
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<FRAUD_CARD>>>>>>\n");
		printf("Transaction  Sequence number is %d\n", seqNum);
		return 0;
	}
}

	