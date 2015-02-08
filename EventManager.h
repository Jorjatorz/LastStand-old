#pragma once

#include "FEngine.h"

#include "Singleton.h"

//Event singleton manager. Holds all the event listeners and is in charge of notifying GENERAL events to all the frameListeners
class EventManager: public Singleton<EventManager>
{
public:
	EventManager();
	~EventManager();

	//Adds a new listener to the listenerList
	void registerEventListener(EventListener* listener);

	//Sends the specific event to all frameListeners
	void keyDownEvent(const KeyboardEvent* eventTriggered);
	void keyUpEvent(const KeyboardEvent* eventTriggered);
	void mouseEvent(const Event* eventTriggered);
	//game started, game fiished, etc, etc

private:
	std::list<EventListener*> mEventListenerList;
};

