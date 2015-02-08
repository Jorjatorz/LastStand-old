#include "FEngine.h"

#include "Root.h"
#include "Pruebas.h"

int main(int argc, char* argv[])
{
	//Create the root
	Root* root = new Root();

	Pruebas p;

	//Run the engine
	root->runEngine();

	delete root;

	system("pause");

	return 0;
}