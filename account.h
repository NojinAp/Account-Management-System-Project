/*
    ==================================================
    Account Management System Project
    ==================================================
*/

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#define ACCT_AGENT 'A'
#define ACCT_CUSTOMER 'C'

struct Person
{
	char name[31];
	int birth_year;
	double income;
	char country[31];
};

struct UserLogin
{
	char username[11];
	char password[9];
};

struct Account
{
	int acc_num;
	char acc_type;
	struct Person person;
	struct UserLogin userlogin;
};

//to get user input for a new account
void getAccount(struct Account* account);
//to get user personal input for a new person
void getPerson(struct Person* person);
//to get user input for a new userlogin
void getUserLogin(struct UserLogin* userlogin);
//to update the variables in the account struct
void updateAccount(struct Account* account);
//to update the variables in the person struct
void updatePerson(struct Person* person);
//to update the variables in the userlogin struct
void updateUserLogin(struct UserLogin* userlogin);

#endif
