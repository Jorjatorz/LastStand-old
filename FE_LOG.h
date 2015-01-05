#pragma once

#include "FEngine.h"

class FE_LOG
{
public:
	//Enumeration with the possible log outputs
	typedef enum
	{
		INFO,
		WARNING,
		ERR
	} tLogType;

	//Prints the text into the console, depending on the type it will show an info, warning or error text.
	FE_LOG(tLogType lType, std::string mesage);
	FE_LOG(tLogType lType, std::string mesage, float num);

	~FE_LOG();

private:

	//Auxiliary functions to print the info,warning,error with color
	void printInfo();
	void printWarning();
	void printError();
};

