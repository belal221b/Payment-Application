#pragma once
/*
 ============================================================================
 Name        : card.h
 Author      : Belal
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#ifndef CARD_CARD_H_
#define CARD_CARD_H_
#include <inttypes.h>

#define NAME_MAX_SIZE 25
#define NAME_MIN_SIZE 20

#define PAN_MAX_SIZE 20
#define PAN_MIN_SIZE 16

#define EXPIRY_DATE_SIZE 5

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[NAME_MAX_SIZE + 1];
	uint8_t cardExpirationDate[EXPIRY_DATE_SIZE + 1];
	uint8_t primaryAccountNumber[PAN_MAX_SIZE];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	OK = 0,
	WRONG_NAME,
	WRONG_EXP_DATE,
	WRONG_PAN
}EN_cardError_t;


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);

#endif /* CARD_CARD_H_ */
#pragma once
