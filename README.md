# **Payment-Application**
This project is a payment application that simulates a transaction between a cardholder and a server through a terminal. It includes four header files each with its own set of functions and structures.

# **Application Flowchart**
![payment-flowchart](https://github.com/belal221b/Payment-Application/assets/84633317/0a7846ab-c680-4619-95d1-965be3445726)

# **app.h**
This header file defines the appStart() function, which is the main function of the application.

# **card.h**
This header file defines the ST_cardData_t structure, which contains the cardholder's name, card expiration date, and primary account number. It also defines the EN_cardError_t enumeration, which represents different types of errors that can occur while getting the card data.

The following functions are defined in this header file:

- getCardHolderName() - gets the cardholder's name.
- getCardExpiryDate() - gets the card's expiration date.
- getCardPAN() - gets the card's primary account number.
- getCardHolderNameTest() - tests the getCardHolderName() function.
- getCardExpiryDateTest() - tests the getCardExpiryDate() function.
- getCardPANTest() - tests the getCardPAN() function.

# **server.h**
This header file defines the EN_transState_t enumeration, which represents the transaction state, and the ST_transaction_t structure, which contains the cardholder data, terminal data, transaction state, and transaction sequence number. It also defines the EN_accountState_t enumeration, which represents the state of the account, and the EN_serverError_t enumeration, which represents different types of errors that can occur while processing the transaction. Finally, it defines the ST_accountsDB_t structure, which contains the balance, state, and primary account number of the account.

The following functions are defined in this header file:

- recieveTransactionData() - receives the transaction data from the terminal.
- isValidAccount() - checks if the card account is valid.
- isBlockedAccount() - checks if the card account is blocked.
- isAmountAvailable() - checks if the transaction amount is available.
- saveTransaction() - saves the transaction data.
- getTransaction() - gets the transaction data based on its sequence number.
- recieveTransactionDataTest() - tests the recieveTransactionData() function.
- isValidAccountTest() - tests the isValidAccount() function.
- isBlockedAccountTest() - tests the isBlockedAccount() function.
- isAmountAvailableTest() - tests the isAmountAvailable() function.
- saveTransactionTest() - tests the saveTransaction() function.

# **terminal.h**
This header file defines the ST_terminalData_t structure, which contains the transaction amount, maximum transaction amount, and transaction date. It also defines the EN_terminalError_t enumeration, which represents different types of errors that can occur while getting the transaction data.

The following functions are defined in this header file:

- getTransactionDate() - gets the transaction date.
- isCardExpired() - checks if the card is expired.
- isValidCardPAN() - checks if the card primary account number is valid.
- getTransactionAmount() - gets the transaction amount.
- isBelowMaxAmount() - checks if the transaction amount is below the maximum allowed amount.
- setMaxAmount() - sets the maximum transaction amount.
- getTransactionDateTest() - tests the getTransactionDate() function.
- isCardExpriedTest() - tests the isCardExpired() function.
- getTransactionAmountTest() - tests the getTransactionAmount() function.
- isBelowMaxAmountTest() - tests the isBelowMaxAmount() function.
- setMaxAmountTest() - tests the setMaxAmount() function.

# **Credits**
This Payment Application Project was created by Belal Mohamed.

