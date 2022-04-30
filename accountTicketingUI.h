/*
    ==================================================
    Account Management System Project
    ==================================================
*/

#ifndef ACCOUNTTICKETINGUI_H_
#define ACCOUNTTICKETINGUI_H_

//to display the detail header
void displayAccountDetailHeader();
//to display the detail record
void displayAccountDetailRecord(const struct Account* account);
//to be an entry point to the application logic
void applicationStartup(struct Account accounts[], int maxsize);
//the login menu function
int menuLogin(struct Account accounts[], int maxsize);
//the main menu for an agent who has authorization to manage the accounts for the system
void menuAgent(struct Account accounts[], int maxsize, struct Account* useraccount);
//to search the array for a match on a desired account number
int findAccountIndexByAcctNum(int accountNum, const struct Account accounts[], int maxsize, int prompt);
//to display a detailed view of all the valid account records
void displayAllAccountDetailRecords(const struct Account accounts[], int maxsize);
//pause execution until user enters the enter key
void pauseExecution(void);

#endif
