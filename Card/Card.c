/*
 ============================================================================
 Name        : card.c
 Author      : Belal
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "card.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


 /*
  * 1. This function will ask for the cardholder's name and store it into card data.
  * 2. Card holder name is 24 characters string max and 20 min.
  * 3. If the cardholder name is NULL, less than 20 characters
  *    or more than 24 will return WRONG_NAME error, else return OK.
 //	scanf("Enter Name", &cardData->cardHolderName);
  */
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Enter Name:  [Max 24 characters - Min 20 characters]");
	printf("\n");
	printf(">>> ");
	gets((char*)cardData->cardHolderName);
	printf("\n");

	if (strlen((const char*)cardData->cardHolderName) > NAME_MAX_SIZE || strlen((const char*)cardData->cardHolderName) < NAME_MIN_SIZE) {
		return WRONG_NAME;
	}
	return OK;
}

/*
 * 1. This function will ask for the card expiry date and store it in card data.
 * 2. Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25".
 * 3. If the card expiry date is NULL, less or more than 5 characters,
 *    or has the wrong format will return WRONG_EXP_DATE error, else return OK.
//	scanf("Enter The Expiration Date", &cardData->cardExpirationDate);
 */
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	char strr[3] = { 0 };
	int temp = 0;
	printf("Enter The Expiration Date: [in the format ""MM/YY""  ""10/25""]\n");
	printf("\n");
	printf(">>> ");
	gets((char*)cardData->cardExpirationDate);
	printf("\n");

	if (strlen((const char*)cardData->cardExpirationDate) < EXPIRY_DATE_SIZE || strlen((const char*)cardData->cardExpirationDate) > EXPIRY_DATE_SIZE) {
		return WRONG_EXP_DATE;
	}
	else {
		// checking month
		strr[0] = cardData->cardExpirationDate[0];
		strr[1] = cardData->cardExpirationDate[1];
		strr[2] = '\0';
		temp = atoi(strr);
		if (temp < 0 || temp > 13) {
			return WRONG_EXP_DATE;
		}
		//checking '/'
		if (cardData->cardExpirationDate[2] != '/') {
			return WRONG_EXP_DATE;
		}
		//checking year
		strr[0] = cardData->cardExpirationDate[3];
		strr[1] = cardData->cardExpirationDate[4];
		strr[2] = '\0';
		temp = atoi(strr);
		if (temp < 0 || temp > 100) {
			return WRONG_EXP_DATE;
		}
		return OK;
	}
}

/*
 * 1. This function will ask for the card's Primary Account Number and store it in card data.
 * 2. PAN is 20 characters alphanumeric only string 19 character max, and 16 character min.
 * 3. If the PAN is NULL, less than 16 or more than 19 characters,
 *    will return WRONG_PAN error, else return OK.
//	scanf("Enter The primary Account Number", &cardData->primaryAccountNumber);
 */
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Enter The primary Account Number: [Max 19 characters and Min 16 characters]\n");
	printf("\n");
	printf(">>> ");
	gets((char*)cardData->primaryAccountNumber);
	printf("\n");

	if (strlen((const char*)cardData->primaryAccountNumber) < PAN_MIN_SIZE || strlen((const char*)cardData->primaryAccountNumber) > PAN_MAX_SIZE) {
		return WRONG_PAN;
	}
	else {
		return OK;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getCardHolderNameTest(void) {

	ST_cardData_t card;

	printf("Tester Name : Belal \n");
	printf("Function Name : getCardHolderName \n");
	printf(" \n");
	printf("Correct input : belal mohamed abdelaziz\n");
	printf("\n");

	if (getCardHolderName(&card) == OK) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : ACCEPTED\n");
		return 0;
	}
	else {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<WRONG_NAME>>>>>>\n");
		printf("Because : 20 characters <= name <= 24 characters\n");
		return 0;
	}
}


void getCardExpiryDateTest(void) {
	ST_cardData_t card;

	printf("Tester Name : Belal \n");
	printf("Function Name : getCardExpiryDateTest \n");
	printf(" \n");
	printf("Correct input : ""10 / 25"" \n");
	printf("\n");

	if (getCardExpiryDate(&card) == OK) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : ACCEPTED\n");
		return 0;
	}
	else {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<WRONG_EXP_DATE>>>>>>\n");
		return 0;
	}
}


void getCardPANTest(void) {
	ST_cardData_t card;
	printf("Tester Name : Belal \n");
	printf("Function Name : getCardPANTest \n");
	printf(" \n");


	printf("Enter The primary Account Number: [Max 19 characters]\n");
	printf("Correct input : 1000000000000000001\n");
	printf("\n");

	if (getCardPAN(&card) == OK) {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : ACCEPTED\n");
		return 0;
	}
	else {
		printf("Expected Result :  ACCEPTED\n");
		printf("Actual Result : <<<<<<WRONG_PAN>>>>>>\n");
		printf("explination : 16 characters <= PAN <= 19 characters\n");
		return 0;
	}
}
