#pragma once
/*
 ============================================================================
 Name        : terminal.h
 Author      : Belal
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#ifndef TERMINAL_TERMINAL_H_
#define TERMINAL_TERMINAL_H_

#include <inttypes.h>
#include <stdlib.h>
#include "Card.h"

#define Trans_DATE_SIZE 10

typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[Trans_DATE_SIZE + 1];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
	OK_FROM_TERMINAL = 0,
	WRONG_DATE,
	EXPIRED_CARD,
	INVALID_CARD,
	INVALID_AMOUNT,
	EXCEED_MAX_AMOUNT,
	INVALID_MAX_AMOUNT
}EN_terminalError_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(const ST_cardData_t* cardData, const ST_terminalData_t* termData);
EN_terminalError_t isValidCardPAN(const ST_cardData_t* cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(const ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);

void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);

#endif /* TERMINAL_TERMINAL_H_ */
