#include "Pruebas.h"

#include "TimerManager.h"
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

	Entity* ent1 = Root::getSingleton()->getSceneManager()->createEntity("b", "Guard.obj");
	SceneNode* node1 = node->createChildSceneNode("b");
	node1->attachObject(ent1);
	node1->setPosition(Vector3(1.0, 0.0, -5.00));

	//For the objects
	ResourceManager::getSingleton()->loadShaderIntoMemoryFromFile("basicObject");

	EventManager::getSingleton()->registerEventListener(this);
}

Pruebas::~Pruebas()
{
}
bool w = false;
bool d = false;
void Pruebas::onKeyDownEvent(const KeyboardEvent* eventTriggered)
{
	if (eventTriggered->mPressedKey == KEYBOARD::ESCAPE)
	{
		Root::getSingleton()->stopEngine();
	}

	if (eventTriggered->mPressedKey == KEYBOARD::W)
	{
		w = true;
	}
	else if (eventTriggered->mPressedKey == KEYBOARD::S)
	{
		Root::getSingleton()->getSceneManager()->getSceneNode("a")->setPosition(Vector3(0.0, 0.0, -1.0));
	}

	if (eventTriggered->mPressedKey == KEYBOARD::D)
	{
		d = true;
	}
	else if (eventTriggered->mPressedKey == KEYBOARD::A)
	{
		Root::getSingleton()->getSceneManager()->getSceneNode("a")->setOrientation(Quaternion());
	}

	if (eventTriggered->mPressedKey == KEYBOARD::G)
	{
		ResourceManager::getSingleton()->reloadAllShadersFromFiles();
	}

	if (eventTriggered->mPressedKey == KEYBOARD::H)
	{
		Root::getSingleton()->getSceneManager()->getEntity("a")->attachNewMesh("Box.obj");
		Root::getSingleton()->getSceneManager()->getSceneNode("a")->setScale(Vector3(0.25));
	}
}
void Pruebas::onKeyUpEvent(const KeyboardEvent* eventTriggered)
{
	if (eventTriggered->mPressedKey == KEYBOARD::W)
	{
		w = false;
	}

	if (eventTriggered->mPressedKey == KEYBOARD::D)
	{
		d = false;
	}
}


void Pruebas::onFrameStartedEvent()
{
	if (w)
	{ 
		Root::getSingleton()->getSceneManager()->getSceneNode("a")->translate(Vector3(0.0, 0.0, -1.00));
	}

	if (d)
	{
		Root::getSingleton()->getSceneManager()->getSceneNode("a")->rotate(Vector3(0.0, 1.0, 0.0), 90);
	}
}