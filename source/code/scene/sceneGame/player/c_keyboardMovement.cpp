#include "c_keyboardMovement.h"

C_KeyboardMovement::C_KeyboardMovement(Object* owner)
	: Component(owner), moveSpeed(2), input(nullptr), collider(nullptr), isMoving(false), reachPosition()
{}

void C_KeyboardMovement::SetInput(Input* input) {
	this->input = input;
}
void C_KeyboardMovement::SetCollider(Collider* collider) {
	this->collider = collider;
}
void C_KeyboardMovement::SetMovementSpeed(int moveSpeed) {
	this->moveSpeed = moveSpeed;
}

bool C_KeyboardMovement::CheckIfDirectionPressed() {
	return (input->IsKeyPressed(Input::Key::Left) ||
		input->IsKeyPressed(Input::Key::Right) ||
		input->IsKeyPressed(Input::Key::Up) ||
		input->IsKeyPressed(Input::Key::Down));
}

void C_KeyboardMovement::Update(float deltaTime) {
	if (input == nullptr || collider == nullptr)
		return;

	sf::Vector2f currentPosition = owner->transform->GetPositionTrainer();
	AnimationState state = animation->GetAnimationState();

	if (isMoving)
		animation->StartUpdating();
	else
		animation->StopUpdating();

	if (state == AnimationState::Idle)
		SetIdle();

	if (isMoving && currentPosition == reachPosition) {
		collider->Delete(oldPosition);
		oldPosition = animToReachPosition(oldPosition, state);
		collider->Add(oldPosition, 2);

		collider->SetY(reachPosition.y);
		isMoving = false;

		Update(deltaTime);
		return;
	}

	if (isMoving) {
		sf::Vector2f move = animToNewPosition(state, moveSpeed);
		owner->transform->AddPosition(move);

		return;
	}

	KeysToMovement(currentPosition);
}

void C_KeyboardMovement::KeysToMovement(sf::Vector2f currentPosition) {
	sf::Vector2f currentPositionBefore = currentPosition;

	bool left = input->IsKeyPressed(Input::Key::Left);
	bool right = input->IsKeyPressed(Input::Key::Right);
	bool up = input->IsKeyPressed(Input::Key::Up);
	bool down = input->IsKeyPressed(Input::Key::Down);

	if (left && collider->FindLeft(currentPosition) == -1) {
		SetAnimationState(AnimationState::WalkLeft);
		currentPosition.x -= 32;
	}
	else if (left)
		SetAnimationState(AnimationState::IdleLeft);

	else if (right && collider->FindRight(currentPosition) == -1) {
		SetAnimationState(AnimationState::WalkRight);
		currentPosition.x += 32;
	}
	else if (right)
		SetAnimationState(AnimationState::IdleRight);

	else if (up && collider->FindUp(currentPosition) == -1) {
		SetAnimationState(AnimationState::WalkUp);
		currentPosition.y -= 32;
	}
	else if (up)
		animation->SetAnimationState(AnimationState::IdleUp);

	else if (down && collider->FindDown(currentPosition) == -1) {
		SetAnimationState(AnimationState::WalkDown);
		currentPosition.y += 32;
	}
	else if (down)
		animation->SetAnimationState(AnimationState::IdleDown);

	else {
		SetIdle();
		return;
	}
	isMoving = (currentPosition != currentPositionBefore);
	reachPosition = currentPosition;
}

void C_KeyboardMovement::Awake() {
	animation = owner->GetComponent<C_Animation>();
}

void C_KeyboardMovement::SetIdle() {
	isMoving = false;
}

void C_KeyboardMovement::SetAnimationState(AnimationState state) {
	animation->SetAnimationState(state);
}
void C_KeyboardMovement::SetOldPosition(float x, float y) {
	SetOldPosition(sf::Vector2f(x, y));
}
void C_KeyboardMovement::SetOldPosition(sf::Vector2f pos) {
	oldPosition = pos;
}