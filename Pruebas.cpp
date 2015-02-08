#include "Pruebas.h"

#include "Entity.h"
#include "SceneManager.h"
#include "SceneNode.h"
#include "Viewport.h"
#include "ResourceManager.h"
#include "Root.h"
#include "RenderWindow.h"
#include "EventManager.h"
#include "KeyboardEvent.h"

Pruebas::Pruebas()
{
	//Initialize engine
	RenderWindow* window = Root::getSingleton()->initEngine("Pruebas");

	//Add a viewport
	window->addViewport(0, 0, 1080, 720);

	Entity* ent = Root::getSingleton()->getSceneManager()->createEntity("a", "Guard.obj");
	SceneNode* node = Root::getSingleton()->getSceneManager()->getRootSceneNode()->createChildSceneNode("a");
	node->attachObject(ent);
	node->setPosition(Vector3(0.0, 0.0, -1.00));

	//For the objects
	ResourceManager::getSingleton()->loadShaderIntoMemoryFromFile("basicObject");

	EventManager::getSingleton()->registerEventListener(this);
}


Pruebas::~Pruebas()
{
}

void Pruebas::onKeyDownEvent(const KeyboardEvent* eventTriggered)
{
	if (eventTriggered->mPressedKey == KEYBOARD::A)
	{
		Root::getSingleton()->getSceneManager()->getSceneNode("a")->translate(Vector3(0.0, 0.0, -0.01));
	}

	if (eventTriggered->mPressedKey == KEYBOARD::D)
	{
		Root::getSingleton()->getSceneManager()->getSceneNode("a")->rotate(Vector3(0.0, 1.0, 0.0), 10);
	}
}

void Pruebas::onKeyUpEvent(const KeyboardEvent* eventTriggered)
{
	FE_LOG(FE_LOG::WARNING, "Key released.");
}