#pragma once
/*
 ============================================================================
 Name        : app.h
 Author      : Belal
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#ifndef APPLICATION_APP_H_
#define APPLICATION_APP_H_


#include "card.h"
#include "terminal.h"
#include "server.h"

typedef enum ST_state
{
	YES, NO
}ST_state;
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
void appStart(void);


#endif /* APPLICATION_APP_H_ */
