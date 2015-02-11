#include "FE_LOG.h"


FE_LOG::FE_LOG(tLogType lType, std::string mesage)
{
	//Look for the correct type and print it
	if (lType == tLogType::INFO)
	{
		printInfo();
		std::cout << mesage << std::endl;
	}
	else if (lType == tLogType::WARNING)
	{
		printWarning();
		std::cout << mesage << std::endl;
	}
	else
	{
		printError();
		std::cout << mesage << std::endl;
	}
}


FE_LOG::~FE_LOG()
{
}

void FE_LOG::printInfo()
{
	std::cout << "[";

	//Change the color
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 11); //Dark grey

	std::cout << "INFO";

	//Change the color
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15); //White

	std::cout << "] ";
}
void FE_LOG::printWarning()
{
	std::cout << "[";

	//Change the color
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 14); //Light Yellow

	std::cout << "WARNING";

	//Change the color
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15); //White

	std::cout << "] ";

}
void FE_LOG::printError()
{
	std::cout << "[";

	//Change the color
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 12); //Light red

	std::cout << "ERROR";

	//Change the color
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15); //White

	std::cout << "] ";
}