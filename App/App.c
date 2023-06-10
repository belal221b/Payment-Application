/*
 ============================================================================
 Name        : app.c
 Author      : Belal
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "App.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ST_transaction_t transData;

void appStart(void) {
	uint32_t test;
	uint32_t i;
	uint8_t istr[1] = { 0 };
	ST_state state;
	uint8_t count;
	EN_transState_t serverState;

	uint8_t seqSTR[3] = { 0 };
	uint32_t transSeqNo = 0;
	while (1) {
		count = 0;
		serverState = OK_FROM_SERVER;
		state = NO;

		printf("1. Enter Card. \n");
		printf("2. Get Transaction \n");
		printf("3. Testing \n");
		//		scanf("%d", &i);
		printf(">>> ");
		gets((char*)istr);
		i = atoi((const char*)istr);
		//		i = 1;
		switch (i) {
		case 1:
			while (1) {
				if (getCardHolderName(&transData.cardHolderData) == OK) {

					//strcpy_s(transData.cardHolderData.cardHolderName, \
						NAME_MAX_SIZE, \
						cardData.cardHolderName);

					count = 0;
					break;
				}
				else {
					printf("Wrong Name \n");
					count++;
					if (count >= 3) break;
				}
			}
			while (1) {
				if (count < 3) {
					if (getCardExpiryDate(&transData.cardHolderData) == OK) {

						//strcpy_s(transData.cardHolderData.cardExpirationDate, \
							EXPIRY_DATE_SIZE + 1, \
							cardData.cardExpirationDate);

						count = 0;
						break;
					}
					else {
						printf("Wrong Expiration Date Format \n");
						count++;
						if (count >= 3) break;
					}
				}
				else {
					break;
				}
			}
			while (1) {
				if (count < 3) {
					if (getCardPAN(&transData.cardHolderData) == OK) {
						//strcpy_s(transData.cardHolderData.primaryAccountNumber,\
								PAN_MAX_SIZE, \
								cardData.primaryAccountNumber);
						count = 0;
						state = YES;
						break;
					}
					else {
						printf("Wrong primary Account Number \n");
						count++;
						if (count >= 3) break;
					}
				}
			}
			break;
		case 2:
			while (1) {
				printf("Enter Transaction Number:  [0 : 254] \n");
				printf("Or -1 for menu \n");
				printf(">>> ");
				gets((char*)&seqSTR);
				transSeqNo = atoi((const char*)seqSTR);
				printf("\n");

				if (transSeqNo == -1) break;

				if (getTransaction(transSeqNo, &transData) == TRANSACTION_NOT_FOUND) {
					printf("Transaction Not Found... \n");
				}

			}
			break;
		case 3:
			while (1) {
				printf("------------------------------------------------\n");
				printf("------------------------------------------------\n");
				printf("1. getCardHolderNameTest\n");
				printf("2. getCardExpiryDateTest\n");
				printf("3. getCardPANTest\n");
				printf("\n");
				printf("4. getTransactionDateTest\n");
				printf("5. isCardExpriedTest\n");
				printf("6. getTransactionAmountTest\n");
				printf("7. isBelowMaxAmountTest\n");
				printf("8. setMaxAmountTest\n");
				printf("\n");
				printf("9. recieveTransactionDataTest\n");
				printf("10. isValidAccountTest\n");
				printf("11. isBlockedAccountTest\n");
				printf("12. isAmountAvailableTest\n");
				printf("13. saveTransactionTest\n");
				printf("\n");
				printf("\n");
				printf(" Enter function test number \n");
				printf("------------------------------------------------\n");
				printf("------------------------------------------------\n");

				printf("Or -1 for menu \n");

				printf("\n");

				printf(">>> ");
				gets((char*)istr);
				test = atoi((const char*)istr);
				switch (test) {
				case 1:
					getCardHolderNameTest();
					break;
				case 2:
					getCardExpiryDateTest();
					break;
				case 3:
					getCardPANTest();
					break;
				case 4:
					getTransactionDateTest();
					break;
				case 5:
					isCardExpriedTest();
					break;
				case 6:
					getTransactionAmountTest();
					break;
				case 7:
					isBelowMaxAmountTest();
					break;
				case 8:
					setMaxAmountTest();
					break;
				case 9:
					recieveTransactionDataTest();
					break;
				case 10:
					isValidAccountTest();
					break;
				case 11:
					isBlockedAccountTest();
					break;
				case 12:
					isAmountAvailableTest();
					break;
				case 13:
					saveTransactionTest();
					break;
				default:
					break;
				}
				if (test > 13 || test < 1)break;
			}
			break;
		default:
			break;
		}
		if (state == YES) {
			count = 0;
			while (1) {
				if (getTransactionDate(&transData.terminalData) == OK_FROM_TERMINAL) {
					count = 0;
					if (isCardExpired(&transData.cardHolderData, &transData.terminalData) == OK_FROM_TERMINAL) {
						if (setMaxAmount(&transData.terminalData) == OK_FROM_TERMINAL) {
							if (getTransactionAmount(&transData.terminalData) == OK_FROM_TERMINAL) {
								if (isBelowMaxAmount(&transData.terminalData) == OK_FROM_TERMINAL) {

									//strcpy_s(transData.terminalData.transactionDate, \
										(Trans_DATE_SIZE + 1), \
										terminalData.transactionDate);

									//transData.terminalData.transAmount = terminalData.transAmount;
									//transData.terminalData.maxTransAmount = terminalData.maxTransAmount;

									serverState = recieveTransactionData(&transData);
									if (serverState == APPROVED) {
										printf("------------------------------------------------\n");
										printf("------------------------------------------------\n");
										printf("Your Balance is Now : %f\n", Balance);
										printf("Transaction  Approved :)\n");
										printf("------------------------------------------------\n");
										printf("------------------------------------------------\n");
										break;
									}
									else if (serverState == DECLINED_STOLEN_CARD) {
										printf("------------------------------------------------\n");
										printf("------------------------------------------------\n");
										printf("ERROR: DECLINED STOLEN CARD \n");
										printf("------------------------------------------------\n");
										printf("------------------------------------------------\n");
										break;
									}
									else if (serverState == DECLINED_INSUFFECIENT_FUND) {
										printf("------------------------------------------------\n");
										printf("------------------------------------------------\n");
										printf("ERROR: DECLINED INSUFFECIENT FUND \n");
										printf("------------------------------------------------\n");
										printf("------------------------------------------------\n");
										break;
									}
									else if (serverState == FRAUD_CARD) {
										printf("------------------------------------------------\n");
										printf("------------------------------------------------\n");
										printf("ERROR: FRAUD CARD \n");
										printf("------------------------------------------------\n");
										printf("------------------------------------------------\n");
										break;
									}
									else if (serverState == INTERNAL_SERVER_ERROR) {
										printf("------------------------------------------------\n");
										printf("------------------------------------------------\n");
										printf("ERROR: INTERNAL SERVER ERROR \n");
										printf("------------------------------------------------\n");
										printf("------------------------------------------------\n");
										break;
									}
									else {
										printf("------------------------------------------------\n");
										printf("------------------------------------------------\n");
										printf("ERROR: INTERNAL SERVER ERROR \n");
										printf("------------------------------------------------\n");
										printf("------------------------------------------------\n");
										break;
									}
								}
								else {
									printf("------------------------------------------------\n");
									printf("------------------------------------------------\n");
									printf("ERROR: EXCEED MAX AMOUNT \n");
									printf("------------------------------------------------\n");
									printf("------------------------------------------------\n");
									break;
								}
							}
							else {
								printf("------------------------------------------------\n");
								printf("------------------------------------------------\n");
								printf("ERROR: INVALID AMOUNT \n");
								printf("------------------------------------------------\n");
								printf("------------------------------------------------\n");
								break;
							}
						}
						else {
							printf("------------------------------------------------\n");
							printf("------------------------------------------------\n");
							printf("ERROR: INVALID MAX AMOUNT \n");
							printf("------------------------------------------------\n");
							printf("------------------------------------------------\n");
							break;
						}
					}
					else {
						printf("------------------------------------------------\n");
						printf("------------------------------------------------\n");
						printf("ERROR: EXPIRED CARD \n");
						printf("------------------------------------------------\n");
						printf("------------------------------------------------\n");
						break;
					}
				}
				else {
					printf("------------------------------------------------\n");
					printf("------------------------------------------------\n");
					printf("Wrong primary Account Number \n");
					printf("------------------------------------------------\n");
					printf("------------------------------------------------\n");
					count++;
					if (count >= 3) break;
				}
			}
		}//END OF STATE

	}// END OF WHILE 1
}
