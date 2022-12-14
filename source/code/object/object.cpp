#include "object.h"
#include "../component/c_pnj/c_pnj.h"

Object::Object() 
	: queuedForRemoval(false), isOn(true) {
	transform = AddComponent<C_Transform>();
}
Object::Object(bool isOn)
	: queuedForRemoval(false), isOn(isOn) {
	transform = AddComponent<C_Transform>();
}
void Object::QueueForRemoval() {
	queuedForRemoval = true;
}
bool Object::IsQueuedForRemoval() {
	return queuedForRemoval;
}

void Object::Awake() {
	for (int i = static_cast<int>(components.size()) - 1; i >= 0; i--)
		components[i]->Awake();
}

void Object::Start() {
	for (int i = static_cast<int>(components.size()) - 1; i >= 0; i--)
		components[i]->Start();
}

void Object::Update(float timeDelta) {
	if (!isOn)
		return;
	for (int i = static_cast<int>(components.size()) - 1; i >= 0; i--)
		components[i]->Update(timeDelta);
}

void Object::LateUpdate(float timeDelta) {
	if (!isOn)
		return;
	for (int i = static_cast<int>(components.size()) - 1; i >= 0; i--)
		components[i]->LateUpdate(timeDelta);
}
void Object::Draw(Window& window) {
	if (!isOn)
		return;
	drawable->Draw(window);
}


void Object::SetOn() { isOn = true; }
void Object::SetOff() { isOn = false; }

bool Object::IsPNJ() {
	return (GetComponent<C_pnj>() != nullptr);
}