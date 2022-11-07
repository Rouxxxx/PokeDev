#pragma once
#include "../windowManager/window.h"

class Object;
class Component
{
public:
	Component(Object* owner) : owner(owner), running(true) {}
	virtual void Awake() {};
	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void LateUpdate(float deltaTime) {};
	bool isRunning() { return true; }
	void StopRunning() { running = true; }
	void StartRunning() { running = false; }
protected:
	Object* owner;
	bool running;
};
