/*
    ==================================================
    Account Management System Project
    ==================================================
    Name   : Nozhin Azarpanah
    Date   : November 14, 2021

*/

#ifndef COMMONHELPERS_H_
#define COMMONHELPERS_H_

//to declare the current year
int currentYear(void);
//to clear the buffer
void clearStandardInputBuffer(void);
//to check if the input is integer
int getInteger();
//to check if the input is a positive integer more than 0
int getPositiveInteger();
//to check if the input is double floating point
double getDouble();
//to check if the input is a positive double floating point
double getPositiveDouble();
//to check if the input is an integer between two points
int getIntFromRange(int lower_bound, int upper_bound);
//to check if the input is from the 2 specific characters or not
char getCharOption(const char* str_input);
//to check the length of the string input
void getCString(char* cstring_input, int lower_bound, int upper_bound);

#endif