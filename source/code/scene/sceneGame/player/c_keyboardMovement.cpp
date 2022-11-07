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

bool C_KeyboardMovement::isDirectionKeyPressed() {
	return input->isDirectionKeyPressed();
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
		isMoving = false;

		Update(deltaTime);
		return;
	}

	if (isMoving) {
		sf::Vector2f move = animToNewPosition(state, moveSpeed);
		owner->transform->AddPosition(move);
		collider->SetY(owner->transform->GetPosition().y);

		return;
	}

	KeysToMovement(currentPosition);
}

void C_KeyboardMovement::KeysToMovement(sf::Vector2f currentPosition) {
	sf::Vector2f currentPositionBefore = currentPosition;
	AnimationState state = GetAnimationState();
	FacingDirection currentFacingDir = animToDir(state);

	if (!isDirectionKeyPressed()) {
		SetIdle();
		return;
	}

	bool left = input->IsKeyPressed(Input::Key::Left);
	bool right = input->IsKeyPressed(Input::Key::Right);
	bool up = input->IsKeyPressed(Input::Key::Up);
	bool down = input->IsKeyPressed(Input::Key::Down);

	if (left && !collider->ExistLeft(currentPosition) && currentFacingDir == FacingDirection::Left) {
		SetAnimationState(AnimationState::WalkLeft);
		currentPosition.x -= 32;
	}
	else if (left)
		SetAnimationState(AnimationState::IdleLeft);

	else if (right && !collider->ExistRight(currentPosition) && currentFacingDir == FacingDirection::Right) {
		SetAnimationState(AnimationState::WalkRight);
		currentPosition.x += 32;
	}
	else if (right)
		SetAnimationState(AnimationState::IdleRight);

	else if (up && !collider->ExistUp(currentPosition) && currentFacingDir == FacingDirection::Up) {
		SetAnimationState(AnimationState::WalkUp);
		currentPosition.y -= 32;
	}
	else if (up)
		animation->SetAnimationState(AnimationState::IdleUp);

	else if (down && !collider->ExistDown(currentPosition) && currentFacingDir == FacingDirection::Down) {
		SetAnimationState(AnimationState::WalkDown);
		currentPosition.y += 32;
	}
	else if (down)
		animation->SetAnimationState(AnimationState::IdleDown);

	isMoving = (currentPosition != currentPositionBefore);
	reachPosition = currentPosition;
	if (isMoving) {
		collider->Delete(currentPositionBefore);
		collider->Add(reachPosition, std::make_shared<Object>(owner));
	}
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
AnimationState C_KeyboardMovement::GetAnimationState() {
	return animation->GetAnimationState();
}
void C_KeyboardMovement::SetOldPosition(float x, float y) {
	SetOldPosition(sf::Vector2f(x, y));
}
void C_KeyboardMovement::SetOldPosition(sf::Vector2f pos) {
	oldPosition = pos;
}