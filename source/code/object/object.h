#pragma once
#include <vector>

#include "../windowManager/window.h"
#include "../component/component.h"
#include "../component/c_transform.h" 
#include "../component/c_drawable.h"
#include "../component/c_textbox.h"
#include "../game/sound/soundFactory.h"


class Object
{
public:
	Object();
	Object(bool isOn);
	std::shared_ptr<C_Transform> transform;
	// Awake is called when object created. Use to ensure 
	// required components are present.
	void Awake();
	void Start();
	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Draw(Window& window);

	void SetOn();
	void SetOff();

	template <typename T> std::shared_ptr<T> GetComponent() {
		// Check that we don't already have a component of this type.
		for (auto& exisitingComponent : components)
			if (std::dynamic_pointer_cast<T>(exisitingComponent))
				return std::dynamic_pointer_cast<T>(exisitingComponent);
		return nullptr;
	};

	bool IsQueuedForRemoval();
	void QueueForRemoval();

	template <typename T> std::shared_ptr<T> AddComponent() {

		for (auto& exisitingComponent : components)
			if (std::dynamic_pointer_cast<T>(exisitingComponent))
				return std::dynamic_pointer_cast<T>(exisitingComponent);

		std::shared_ptr<T> newComponent = std::make_shared<T>(this);
		components.push_back(newComponent);

		if (std::dynamic_pointer_cast<C_Drawable>(newComponent))
			drawable = std::dynamic_pointer_cast<C_Drawable>(newComponent);

		return newComponent;
	};
	std::shared_ptr<C_Drawable> GetDrawable() {
		return drawable;
	}

	std::shared_ptr<C_TextBox> getTextBoxComponent();
	void SetTextBox(std::shared_ptr<Object>);
	void SetSoundFactory(std::shared_ptr<SoundFactory>);

private:
	std::vector<std::shared_ptr<Component>> components;
	std::shared_ptr<Object> textBoxPtr;
	std::shared_ptr<C_Drawable> drawable;
	std::shared_ptr<SoundFactory> soundFactory;
	bool queuedForRemoval;
	bool isOn;
};
