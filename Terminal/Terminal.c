/*
 ============================================================================
 Name        : terminal.c
 Author      : Belal
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "terminal.h"


 /*
  * 1. This function will ask for the transaction data and store it in terminal data.
  * 2. Transaction date is 10 characters string in the format DD/MM/YYYY, e.g 25/06/2022.
  * 3. If the transaction date is NULL, less than 10 characters or wrong format/
  *    will return WRONG_DATE error, else return OK.
 //	scanf("Enter The Transaction Date", &termData->transactionDate);
  */

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	char strr[3] = { 0 };
	int temp = 0;
	printf("Enter The Transaction Date:  [in the format DD/MM/YYYY, e.g 25/06/2022]\n");
	printf(">>> ");
	gets(&termData->transactionDate);
	printf("\n");

	if (strlen((const char*)termData->transactionDate) != Trans_DATE_SIZE) {
		return WRONG_DATE;
	}
	else {
		/*
		 * characters string in the format DD / MM / YYYY
		 * 								   01 2 34 5 6789
		 */

		 // checking day
		strr[0] = termData->transactionDate[0];
		strr[1] = termData->transactionDate[1];
		strr[2] = '\0';
		temp = atoi(strr);
		if (temp < 0 || temp > 32) {
			return WRONG_DATE;
		}

		//checking '/'
		if (termData->transactionDate[2] != '/') {
			return WRONG_DATE;
		}

		// checking month
		strr[0] = termData->transactionDate[3];
		strr[1] = termData->transactionDate[4];
		strr[2] = '\0';
		temp = atoi(strr);
		if (temp < 0 || temp > 13) {
			return WRONG_DATE;
		}

		//checking '/'
		if (termData->transactionDate[5] != '/') {
			return WRONG_DATE;
		}

		// checking year
		strr[0] = termData->transactionDate[6];
		strr[1] = termData->transactionDate[7];
		strr[0] = termData->transactionDate[8];
		strr[1] = termData->transactionDate[9];
		strr[2] = '\0';
		temp = atoi(strr);
		if (temp >= 2000) {
			return WRONG_DATE;
		}
		return OK_FROM_TERMINAL;
	}

}

/*
 * 1. This function compares the card expiry date with the transaction date.
 * 2. If the card expiration date is before the transaction date/
 * 	  will return EXPIRED_CARD, else return OK.
 */
EN_terminalError_t isCardExpired(const ST_cardData_t* cardData, const ST_terminalData_t* termData) {
	char str[3] = { 0 };
	int expirationDateM, expirationDateY, tramsactionDateM, tramsactionDateY;

	/*
	 * Expiration Date is in the format "MM/YY"
	 */
	str[0] = cardData->cardExpirationDate[3];
	str[1] = cardData->cardExpirationDate[4];
	str[2] = '\0';
	expirationDateY = atoi(str);
	/*
	 * Transaction Date is in the format DD / MM / YYYY
	 *                                   01 2 34 5 6789
	 */
	str[0] = termData->transactionDate[8];
	str[1] = termData->transactionDate[9];
	str[2] = '\0';
	tramsactionDateY = atoi(str);

	if (expirationDateY < tramsactionDateY) {
		return EXPIRED_CARD;
	}
	else {
		/*
		 * Expiration Date is in the format "MM/YY"
		 */
		str[0] = cardData->cardExpirationDate[0];
		str[1] = cardData->cardExpirationDate[1];
		str[2] = '\0';
		expirationDateM = atoi(str);
		/*
		 * Transaction Date is in the format DD / MM / YYYY
		 */
		str[0] = termData->transactionDate[3];
		str[1] = termData->transactionDate[4];
		str[2] = '\0';
		tramsactionDateM = atoi(str);

		if (expirationDateM < tramsactionDateM) {
			return EXPIRED_CARD;
		}
		else {
			return OK_FROM_TERMINAL;
		}
	}

}

EN_terminalError_t isValidCardPAN(const ST_cardData_t* cardData) {
	int pan;
	pan = atoi(cardData->primaryAccountNumber);

	if (pan != 0) {
		if (strlen((const char*)cardData->primaryAccountNumber) < PAN_MIN_SIZE || strlen((const char*)cardData->primaryAccountNumber) > PAN_MAX_SIZE) {
			return WRONG_PAN;
		}
	}
	return OK_FROM_TERMINAL;

}

/*
 * 1. This function asks for the transaction amount and saves it into terminal data.
 * 2. If the transaction amount is less than or equal to 0 /
 *    will return INVALID_AMOUNT, else return OK.
 */
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	char str[32] = { 0 };
	float x;
	printf("Enter The Transaction Amount\n");
	printf("\n");
	printf(">>> ");
	gets((char*)str);
	printf("\n");
	x = atof(str);
	termData->transAmount = atof(str);

	if (termData->transAmount <= 0) {
		return INVALID_AMOUNT;
	}
	else {
		return OK_FROM_TERMINAL;
	}
}

/*
 * 1. This function compares the transaction amount with the terminal max amount.
 * 2. If the transaction amount is larger than the terminal max amount/
 *    will return EXCEED_MAX_AMOUNT, else return OK.
 */
EN_terminalError_t isBelowMaxAmount(const ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount) {
		return EXCEED_MAX_AMOUNT;
	}
	else {
		return OK_FROM_TERMINAL;
	}
}

/*
 * 1. This function sets the maximum allowed amount into terminal data.
 * 2. Transaction max amount is a float number.
 * 3. If transaction max amount less than or equal to 0 will return/
 *    INVALID_MAX_AMOUNT error, else return OK.
 */
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	char str[32];

	printf("Enter The max Transaction Amount");
	printf("\n");
	printf(">>> ");
	gets((char*)str);
	printf("\n");
	termData->maxTransAmount = atof(str);

	if (termData->maxTransAmount <= 0) {
		return INVALID_MAX_AMOUNT;
	}
	else {
		return OK_FROM_TERMINAL;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1
void getTransactionDateTest(void) {
	ST_terminalData_t terminal;

	printf("Tester Name : Belal \n");
	printf("Function Name : getTransactionDateTest \n");
	printf(" \n");
	printf("Correct input : 25/06/2022\n");
	printf("\n");

	if (getTransactionDate(&terminal) == OK) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : ACCEPTED\n");
		return 0;
	}
	else {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<WRONG_DATE>>>>>>\n");
		return 0;
	}
}

// 2
void isCardExpriedTest(void) {

	ST_terminalData_t terminal;
	ST_cardData_t card;

	printf("Tester Name : Belal \n");
	printf("Function Name : isCardExpriedTest \n");
	printf(" \n");

	printf("For Expiry Date\n");
	printf("Correct input : 12/28\n");
	if (getCardExpiryDate(&card) != OK_FROM_TERMINAL) {
		printf(" WRONG_EXP_DATE \n");
		return 0;
	}
	printf("For Transaction Date\n");
	printf("Correct input : 25/06/2022\n");
	if (getTransactionDate(&terminal) != OK_FROM_TERMINAL) {
		printf(" WRONG_DATE \n");
		return 0;
	}
	
	printf("\n");

	if (isCardExpired(&card, &terminal) == OK_FROM_TERMINAL) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : ACCEPTED\n");
		return 0;
	}
	else {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<EXPIRED_CARD>>>>>>\n");
		return 0;
	}
}

// 3
void getTransactionAmountTest(void) {

	ST_terminalData_t terminal;

	printf("Tester Name : Belal \n");
	printf("Function Name : getTransactionAmountTest \n");
	printf("\n");
	
	
	printf(" \n");

	if (getTransactionAmount(&terminal) == OK_FROM_TERMINAL) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : ACCEPTED\n");
		return 0;
	}
	else {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<INVALID_AMOUNT>>>>>>\n");
		return 0;
	}
}

// 4
void isBelowMaxAmountTest(void) {
	ST_terminalData_t terminal;

	printf("Tester Name : Belal \n");
	printf("Function Name : isBelowMaxAmount \n");
	printf("\n");

	if (setMaxAmount(&terminal) != OK_FROM_TERMINAL) {
		printf(" INVALID_MAX_AMOUNT \n");
		return 0;
	}
	printf(" \n");
	if (getTransactionAmount(&terminal) != OK_FROM_TERMINAL) {
		printf(" INVALID_AMOUNT \n");
		return 0;
	}


	if (isBelowMaxAmount(&terminal) == OK_FROM_TERMINAL) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : ACCEPTED\n");
		return 0;
	}
	else {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<EXCEED_MAX_AMOUNT>>>>>>\n");
		return 0;
	}
}

// 5
void setMaxAmountTest(void) {
	ST_terminalData_t terminal;

	printf(" \n");
	printf("Tester Name : Belal \n");
	printf("Function Name : setMaxAmountTest \n");
	printf(" \n");

	if (setMaxAmount(&terminal) == OK_FROM_TERMINAL) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : ACCEPTED\n");
		return 0;
	}
	else {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<INVALID_MAX_AMOUNT>>>>>>\n");
		return 0;
	}
}