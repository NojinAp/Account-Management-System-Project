/*
    ==================================================
    Account Management System Project
    ==================================================
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "accountTicketingUI.h"
#include "account.h"
#include "commonHelpers.h"

//default flag is 1
int flag = 1;

void displayAccountDetailHeader() 
{
	printf("Acct# Acct.Type Full Name       Birth Income      Country    Login      Password\n");
	printf("----- --------- --------------- ----- ----------- ---------- ---------- --------\n");
}

void displayAccountDetailRecord(const struct Account* account) 
{
	int i;
	char* accounttype[10];
	if (account->acc_type == 'C') 
	{
		*accounttype = "CUSTOMER";
	}
	else if (account->acc_type == 'A') 
	{
		*accounttype = "AGENT";
	}
	char hiddenpass[9];
	strcpy(hiddenpass, account->userlogin.password);
	const int passlength = 8;
	for (i = 0; i < passlength; i++)
	{
		if (i % 2 != 0)
		{
			hiddenpass[i] = '*';
		}
	}
	printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s", account->acc_num, *accounttype, account->person.name, account->person.birth_year, account->person.income, account->person.country, account->userlogin.username, hiddenpass);
	printf("\n");
}

void applicationStartup(struct Account accounts[], int maxsize)
{
	do 
	{
		menuLogin (accounts, maxsize);
	} while (flag == 1);
}

int menuLogin(struct Account accounts[], int maxsize) 
{
	int selection, i, userindex, accountNum;

	do 
	{
		userindex = -1;
		printf("==============================================\nAccount Ticketing System - Login\n==============================================\n");
		printf("1) Login to the system\n0) Exit application\n----------------------------------------------\n\nSelection: ");
		selection = getIntFromRange(0, 1);
		switch (selection) 
		{
		case 0:
			printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
			char exit;
			exit = getCharOption("yYnN");
			if (exit == 'Y' || exit == 'y') 
			{
				flag = 0;
				printf("\n==============================================\nAccount Ticketing System - Terminated\n==============================================\n");
			}
			else 
			{
				printf("\n");
			}
			break;
		case 1:
		        char pass[99] = { 0 };
			printf("\nEnter your account#: ");
			accountNum = getPositiveInteger();
			printf("\nEnter your password: ");
			scanf("%s", pass);
			for (i = 0; i < maxsize; i++)
			{
				if (accountNum == accounts[i].acc_num && accounts[i].acc_type == 'A' && strcmp(pass, accounts[i].password) == 0)
				{
					userindex = i;
					printf("\n");
					menuAgent(accounts, maxsize, &accounts[userindex]);
				}
			}
			if (userindex < 0) 
			{
				printf("ERROR:  Login failed!\n\n");
				pauseExecution();
				printf("\n");
			}
			break; 
		}
	} while (flag == 1);
	return userindex;
}

void menuAgent(struct Account accounts[], int maxsize, struct Account* useraccount) 
{
	int flag = 1;
	int accountNum;
	int i = 0;
	int firstEmptyIndex = -1;
	int arrayIndex = -1;
	do
	{
		for (i = 0; i < maxsize; i++)
		{
			if (accounts[i].acc_num == 0)
			{
				firstEmptyIndex = i;
				break;
			}
		}
		printf("AGENT: %s (%d)", useraccount->person.name, useraccount->acc_num);
		printf("\n==============================================\nAccount Ticketing System - Agent Menu\n==============================================\n");
		printf("1) Add a new account\n2) Modify an existing account\n3) Remove an account\n4) List accounts: detailed view\n----------------------------------------------\n0) Logout\n\n");
		printf("Selection: ");
		int selection;
		selection = getIntFromRange(0, 4);
		switch (selection) {
		case 1:
			if (firstEmptyIndex < 0)
			{
				printf("\nERROR:  Account listing is FULL, call ITS Support!\n\n");
			}
			else
			{
				getAccount(&accounts[firstEmptyIndex]);
				getPerson(&accounts[firstEmptyIndex].person);
				if (accounts[firstEmptyIndex].acc_type == 'A') {
					getUserLogin(&accounts[firstEmptyIndex].userlogin);
				}
				printf("*** New account added! ***\n\n");
				pauseExecution();
				printf("\n");
			}
				break;
		case 2:
			printf("\nEnter the account#: ");
			accountNum = getPositiveInteger();
			printf("\n");
			for (i = 0; i < maxsize; i++)
			{
				if (accountNum == accounts[i].acc_num)
				{
					arrayIndex = i;
					break;
				}
			}
			if (arrayIndex < 0)
			{
				printf("\nERROR: Not Found.\n\n");
			}
			else
			{
				updateAccount(&accounts[arrayIndex]);
			}
			break;
		case 3:
			printf("\nEnter the account#: ");
			accountNum = getPositiveInteger();
			for (i = 0; i < maxsize; i++)
			{
				if (accountNum == accounts[i].acc_num)
				{
					arrayIndex = i;
					break;
				}
			}
			if (arrayIndex < 0)
			{
				printf("\nERROR: Not Found.\n\n");
			}
			else
			{
				if (accounts[arrayIndex].acc_num == useraccount->acc_num) 
				{
					printf("\nERROR: You can't remove your own account!\n\n");
					pauseExecution();
					printf("\n");
				}
				else 
				{
					displayAccountDetailHeader();
					displayAccountDetailRecord(&accounts[arrayIndex]);
					printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
					char remove;
					remove = getCharOption("YN");
					if (remove == 'Y') 
					{
						accounts[arrayIndex].acc_num = 0;
						printf("\n*** Account Removed! ***\n\n");
						pauseExecution();
						printf("\n");
					}
				}
			}
			break;
		case 4:
			printf("\n");
			displayAllAccountDetailRecords(accounts, maxsize);
			printf("\n");
			pauseExecution();
			printf("\n");
			break;
		case 0:
			printf("\n### LOGGED OUT ###\n\n");
			flag = 0;
			break;
		}
	} while (flag == 1);
}

void displayAllAccountDetailRecords(const struct Account accounts[], int maxsize) 
{
	int i;
	displayAccountDetailHeader();
	for (i = 0; i < maxsize; i++) 
	{
		if (accounts[i].acc_num > 0) 
		{
			displayAccountDetailRecord(&accounts[i]);
		}
	}
}

void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
}
