#include "c_keyboard.h"

C_Keyboard::C_Keyboard(Object* owner)
	: Component(owner), moveSpeed(2), input(nullptr), collider(nullptr), isMoving(false), isInteracting(false), reachPosition()
{}


void C_Keyboard::Update(float deltaTime) {
	if (input == nullptr || collider == nullptr)
		return;

	sf::Vector2f currentPosition = owner->transform->GetPositionTrainer();

	UpdateInteractions(deltaTime);
	UpdateMovement(deltaTime, currentPosition);
}