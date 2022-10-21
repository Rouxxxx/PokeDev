#include "objectCollection.h"

void ObjectCollection::Add(std::shared_ptr<Object> object) {
	newObjects.push_back(object);
}
void ObjectCollection::Add(std::vector<std::shared_ptr<Object>> vector) {
	for (std::shared_ptr<Object> object : vector)
		Add(object);
}

void ObjectCollection::Update(float deltaTime) {
	for (auto& o : objects)
		o->Update(deltaTime);
}
void ObjectCollection::LateUpdate(float deltaTime) {
	for (auto& o : objects)
		o->LateUpdate(deltaTime);
}
void ObjectCollection::Draw(Window& window) {
	drawables.Draw(window);
}


void ObjectCollection::ProcessNewObjects() {
	if (newObjects.size() == 0)
		return;
	
	for (const auto& o : newObjects)
		o->Awake();
	for (const auto& o : newObjects)
		o->Start();

	objects.insert(objects.end(), newObjects.begin(), newObjects.end());
	drawables.Add(newObjects);
	newObjects.clear();
}

void ObjectCollection::ProcessRemovals() {
	auto objIterator = objects.begin();
	while (objIterator != objects.end())
	{
		auto obj = **objIterator;
		if (obj.IsQueuedForRemoval())
			objIterator = objects.erase(objIterator);
		else
			++objIterator;
	}

	drawables.ProcessRemovals();
}
