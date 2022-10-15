#pragma once
#include "../windowManager/window.h"

class Object;
class Component
{
public:
	Component(Object* owner) : owner(owner) {}
	virtual void Awake() {};
	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void LateUpdate(float deltaTime) {};
	virtual void Draw(Window& window) {};
protected:
	Object* owner;
};
