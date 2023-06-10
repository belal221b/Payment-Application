#pragma once
/*
 ============================================================================
 Name        : server.h
 Author      : Belal
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_
#include "card.h"
#include "terminal.h"

#define ACCOUNTS	255

float Balance;

typedef enum EN_transState_t
{
	APPROVED,
	DECLINED_INSUFFECIENT_FUND,
	DECLINED_STOLEN_CARD,
	FRAUD_CARD,
	INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_accountState_t
{
	RUNNING,
	BLOCKED
}EN_accountState_t;

typedef enum EN_serverError_t
{
	OK_FROM_SERVER = 0,
	SAVING_FAILED,
	TRANSACTION_NOT_FOUND,
	ACCOUNT_NOT_FOUND,
	LOW_BALANCE,
	BLOCKED_ACCOUNT
}EN_serverError_t;

typedef struct ST_accountsDB_t
{
	float balance;
	EN_accountState_t state;
	uint8_t primaryAccountNumber[PAN_MAX_SIZE];
}ST_accountsDB_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(const ST_cardData_t* cardData);
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence);
EN_serverError_t isAmountAvailable(const ST_terminalData_t* termData);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
EN_serverError_t getTransaction(const uint32_t transactionSequenceNumber, const ST_transaction_t* transData);

void recieveTransactionDataTest(void);
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);

#endif /* SERVER_SERVER_H_ */
