/*
    ==================================================
    Account Management System Project
    ==================================================
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "account.h"
#include "commonHelpers.h"

void getAccount(struct Account* account) 
{
	printf("\nAccount Data: New Record\n----------------------------------------\n");
	printf("Enter the account number: ");
	account -> acc_num = getInteger();
	printf("\nEnter the account type (A=Agent | C=Customer): ");
	account->acc_type = getCharOption("AC");
	printf("\n");
}

void getPerson(struct Person* person) 
{
	printf("Person Data Input\n----------------------------------------\n");
	printf("Enter the person's full name (30 chars max): ");
	getCString(person -> name, 1 , 30);
	printf("Enter birth year (current age must be between 18 and 110): ");
	person->birth_year = getIntFromRange(currentYear() - 110, currentYear() - 18);
	printf("Enter the household Income: $");
	person->income = getPositiveDouble();
	printf("Enter the country (30 chars max.): ");
	getCString(person->country, 1, 30);
	printf("\n");
}

void getUserLogin(struct UserLogin* userlogin) 
{
	printf("User Login Data Input\n----------------------------------------\n");
	printf("Enter user login (10 chars max): ");
	getCString(userlogin->username, 1, 10);
	printf("Enter the password (must be 8 chars in length): ");
	getCString(userlogin->password, 8, 8);
	printf("\n");
}

void updateAccount(struct Account* account) 
{
	int flag = 1;
	do {
		printf("Update Account: %d (%s)\n----------------------------------------\n", account->acc_num, account->person.name);
		printf("1) Update account type (current value: %c)\n2) Person\n3) Login\n0) Done\nSelection: ", account->acc_type);
		int selection;
		selection = getIntFromRange(0, 3);
		switch (selection) 
		{
		case 1:
			printf("\nEnter the account type (A=Agent | C=Customer): ");
			char type;
			type = getCharOption("AC");
			if (type == 'A') 
			{
				printf("\nAgent type accounts require a user login.  Please enter this information now:\n\n");
				account->acc_type = 'A';
				getUserLogin(&account->userlogin);
			} 
			else if (type == 'C') 
			{
				account->acc_type = 'C';
				struct UserLogin zero = { {0} };
				account->userlogin = zero;
				printf("\n");
			}
			break;
		case 2:
			updatePerson(&account->person);
			break;
		case 3:
			if (account->acc_type == 'C') 
			{
				printf("\nERROR:  Customer account types don't have user logins!\n\n");
			}
			else 
			{
				updateUserLogin(&account->userlogin);
			}
			break;
		case 0:
			printf("\n");
			flag = 0;
			break;
		}
	} while (flag == 1);
}

void updatePerson(struct Person* person) 
{
	int flag = 1;
	do 
	{
		printf("\nPerson Update Options\n----------------------------------------\n");
		printf("1) Full name (current value: %s)\n", person->name);
		printf("2) Household Income (current value: $%.2lf)\n", person->income);
		printf("3) Country (current value: %s)\n0) Done\nSelection: ", person->country);
		int selection;
		selection = getIntFromRange(0, 3);
		switch (selection) 
		{
		case 1:
			printf("\nEnter the person's full name (30 chars max): ");
			getCString(person->name, 1, 30);
			break;
		case 2:
			printf("\nEnter the household Income: $");
			person->income = getPositiveDouble();
			break;
		case 3:
			printf("\nEnter the country (30 chars max.): ");
			getCString(person->country, 1, 30);
			break;
		case 0:
			printf("\n");
			flag = 0;
			break;
		}
	} while (flag == 1);
}

void updateUserLogin(struct UserLogin* userlogin) 
{
	int flag = 1;
	do 
	{
		printf("\nUser Login: %s - Update Options\n----------------------------------------\n", userlogin->username);
		printf("1) Password\n0) Done\nSelection: ");
		int selection;
		selection = getIntFromRange(0, 1);
		switch (selection) {
		case 1:
			printf("\nEnter the password (must be 8 chars in length): ");
			getCString(userlogin->password, 8, 8);
			break;
		case 0:
			printf("\n");
			flag = 0;
			break;
		}
	} while (flag == 1);
}
