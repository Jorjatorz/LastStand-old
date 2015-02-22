#include "Pruebas.h"

#include "Camera.h"
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
#include "MouseEvent.h"
#include "InputManager.h"

Pruebas::Pruebas()
	:transW(false),
	transS(false),
	transA(false),
	transD(false)
{
	//Initialize engine
	RenderWindow* window = Root::getSingleton()->initEngine("Pruebas");

	//Create camera
	Camera* cam = Root::getSingleton()->getSceneManager()->createCamera("viewCamera");

	//Add a viewport
	window->addViewport(cam, 0, 0, 1080, 720);

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

void Pruebas::onKeyDownEvent(const KeyboardEvent* eventTriggered)
{
	if (eventTriggered->mPressedKey == KEYBOARD::ESCAPE)
	{
		Root::getSingleton()->stopEngine();
	}

	if (eventTriggered->mPressedKey == KEYBOARD::W)
	{
		transW = true;
	}
	else if (eventTriggered->mPressedKey == KEYBOARD::S)
	{
		transS = true;
	}

	if (eventTriggered->mPressedKey == KEYBOARD::D)
	{
		transD = true;
	}
	else if (eventTriggered->mPressedKey == KEYBOARD::A)
	{
		transA = true;
	}

	if (eventTriggered->mPressedKey == KEYBOARD::G)
	{
		ResourceManager::getSingleton()->reloadAllShadersFromFiles();
	}
}
void Pruebas::onKeyUpEvent(const KeyboardEvent* eventTriggered)
{
	if (eventTriggered->mPressedKey == KEYBOARD::W)
	{
		transW = false;
	}
	else if (eventTriggered->mPressedKey == KEYBOARD::S)
	{
		transS = false;
	}

	if (eventTriggered->mPressedKey == KEYBOARD::D)
	{
		transD = false;
	}
	else if (eventTriggered->mPressedKey == KEYBOARD::A)
	{
		transA = false;
	}
}

bool a = false;
void Pruebas::onMouseEvent(const MouseEvent* eventTriggered)
{
	if (eventTriggered->mButtonActionType == MouseEvent::BUTTON_DOWN)
	{
		if (eventTriggered->mButton == MOUSE::LEFT)
		{
			a = true;
		}
	}


	if (eventTriggered->mButtonActionType == MouseEvent::BUTTON_UP)
	{
		if (eventTriggered->mButton == MOUSE::LEFT)
		{
			a = false;
		}
	}
}


void Pruebas::onFrameStartedEvent()
{
	if (transW)
	{
		Root::getSingleton()->getSceneManager()->getCamera("viewCamera")->translate(Vector3(0.0, 0.0, -5.0));
	}
	else if (transS)
	{
		Root::getSingleton()->getSceneManager()->getCamera("viewCamera")->translate(Vector3(0.0, 0.0, 5.0));
	}

	if (transA)
	{
		Root::getSingleton()->getSceneManager()->getCamera("viewCamera")->translate(Vector3(-5.0, 0.0, 0.0));
	}
	else if (transD)
	{
		Root::getSingleton()->getSceneManager()->getCamera("viewCamera")->translate(Vector3(5.0, 0.0, 0.0));
	}

	if (a)
	{
		Root::getSingleton()->getSceneManager()->getCamera("viewCamera")->yaw(1 * 180 / 3.14);

		Quaternion quat = Root::getSingleton()->getSceneManager()->getCamera("viewCamera")->getOrientation();
		Vector3 finalOrientation = Math::toEulerAngles(quat);

		std::cout << quat.getW() << " " << quat.getX() << " " << quat.getY() << " " << quat.getZ() << std::endl;
		//std::cout << finalOrientation.x << " " << finalOrientation.y << " " << finalOrientation.z << std::endl;
	}
}