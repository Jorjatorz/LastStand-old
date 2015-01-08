#include "FEngine.h"

#include "Root.h"

int main(int argc, char* argv[])
{
	Root* root = new Root();

	root->initEngine("Pruebas");

	root->runEngine();

	delete root;

	system("pause");

	return 0;
}