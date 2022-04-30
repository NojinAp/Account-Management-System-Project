/*
    ==================================================
    Account Management System Project
    ==================================================
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>

#include "commonHelpers.h"

int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}

void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing
	}
}

int getInteger() 
{
	int Intvalue;
	char newLine = 'x';
	do 
	{
		scanf("%d%c", &Intvalue, &newLine);
		if (newLine != '\n') 
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
	} while (newLine != '\n');
	return Intvalue;
}

int getPositiveInteger() 
{
	int positiveIntvalue = getInteger();
	do 
	{
		if (positiveIntvalue <= 0) 
		{
			printf("ERROR: Value must be a positive integer greater than zero: ");
			scanf("%d", &positiveIntvalue);
		}
	} while (positiveIntvalue <= 0);
	return positiveIntvalue;
}

double getDouble() 
{
	double Doublevalue;
	char newLine = 'x';
	do 
	{
		scanf("%lf%c", &Doublevalue, &newLine);
		if (newLine != '\n') 
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
	} while (newLine != '\n');
	return Doublevalue;
}

double getPositiveDouble() 
{
	double positiveDoublevalue = getDouble();
	do 
	{
		if (positiveDoublevalue <= 0) 
		{
			printf("ERROR: Value must be a positive double floating-point number: ");
			scanf("%lf", &positiveDoublevalue);
			clearStandardInputBuffer();
		}
	} while (positiveDoublevalue <= 0);
	return positiveDoublevalue;
}

int getIntFromRange(int lower_bound, int upper_bound) 
{
	int intValue = 0;
	char newLine;
	do
	{
		newLine = 'n';
		scanf("%d%c", &intValue, &newLine);
		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
		else if (intValue < lower_bound || intValue > upper_bound)
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", lower_bound, upper_bound);
		}
	} while (newLine != '\n' || intValue < lower_bound || intValue > upper_bound);
	return intValue;
}

char getCharOption(const char* str_input) 
{
	char char_input;
	char char_EOL = 0;
	int valid_flag = 0;
	int i = 0;
	do 
	{
		scanf("%c%c", &char_input, &char_EOL);
		if (char_EOL == '\n') 
		{
			i = 0;
			while (str_input[i] != 0 && valid_flag == 0) 
			{
				if (str_input[i] == char_input) 
				{
					valid_flag = 1;
				}
				else 
				{
					i++;
				}
			}
		}
		else 
		{
			clearStandardInputBuffer();
		}
		if (valid_flag == 0) 
		{
			printf("ERROR: Character must be one of [%s]: ", str_input);

		}
	} while (valid_flag == 0);
	return char_input;
}

void getCString(char* cstring_input, int lower_bound, int upper_bound) 
{
	char char_EOL = 0;
	int valid_flag = 0;
	int terminated_flg = 0;
	char cstring_scan[100];
	int count = 0;
	int i = 0;
	do 
	{
		scanf("%[^\n]%c", cstring_scan, &char_EOL);
		if (char_EOL == '\n') {
			count = 0;
			valid_flag = 0;
			while (valid_flag == 0) 
			{
				if (cstring_scan[count] == 0) 
				{
					valid_flag = 1;
				}
				else 
				{
					count++;
				}
			}
			if (count >= lower_bound && count <= upper_bound)
			{
				for (i = 0; i < count; i++) 
				{
					cstring_input[i] = cstring_scan[i];
				}
				cstring_input[count] = 0;
				terminated_flg = 1;
			}
			else if (count != lower_bound && upper_bound == lower_bound) 
			{
				printf("ERROR: String length must be exactly %d chars: ", lower_bound);
			}
			else if (count > upper_bound)
			{
				printf("ERROR: String length must be no more than %d chars: ", upper_bound);
			}
			else if (count < lower_bound)
			{
				printf("ERROR: String length must be between %d and %d chars: ", lower_bound, upper_bound);
			}
		}
	} while (terminated_flg == 0);
	return;
}
