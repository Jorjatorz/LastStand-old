#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

class FE_LOG
{
	//Private copy constructor
	FE_LOG(const FE_LOG&);

public:
	//Enumeration with the possible log outputs
	typedef enum
	{
		INFO,
		WARNING,
		ERR
	} tLogType;

	//Prints a text into the console, depending on the type it will show an info, warning or error text.
	FE_LOG(tLogType lType, std::string mesage);
	//Prints a text with a float number into the console, depending on the type it will show an info, warning or error text.
	FE_LOG(tLogType lType, std::string mesage, float num);

	~FE_LOG();

private:

	//Auxiliary functions to print the info,warning,error with color
	void printInfo();
	void printWarning();
	void printError();
};

