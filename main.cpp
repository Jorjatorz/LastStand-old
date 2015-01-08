#include "FEngine.h"

#include "Root.h"
#include "RenderWindow.h"
#include "Viewport.h"

int main(int argc, char* argv[])
{
	//Create the root
	Root* root = new Root();

	//Initialize engine
	RenderWindow* window = root->initEngine("Pruebas");

	{
		//Add a viewport
		window->addViewport(0, 0, 1080, 720);
	}

	//Run the engine
	root->runEngine();

	delete root;

	system("pause");

	return 0;
}