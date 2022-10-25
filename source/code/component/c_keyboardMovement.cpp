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

	if (!isMoving)
		animation->StopUpdating();
	else
		animation->StartUpdating();

	sf::Vector2f currentPosition = owner->transform->GetPosition();
	//currentPosition.x -= 16;
	currentPosition.y += 8;
	sf::Vector2f currentPositionBefore = owner->transform->GetPosition();
	AnimationState state = animation->GetAnimationState();

	if (state == AnimationState::Idle)
		SetIdle();

	if (isMoving && currentPosition == reachPosition) {
		SetIdle();
		Update(deltaTime);
		return;
	}

	if (isMoving) {
		int xMove = 0;
		int yMove = 0;
		
		if (state == AnimationState::RunDown)
			yMove = moveSpeed * 2;
		else if (state == AnimationState::WalkDown)
			yMove = moveSpeed;

		else if (state == AnimationState::RunUp)
			yMove = -moveSpeed * 2;
		else if (state == AnimationState::WalkUp)
			yMove = -moveSpeed;

		else if (state == AnimationState::RunLeft)
			xMove = -moveSpeed * 2;
		else if (state == AnimationState::WalkLeft)
			xMove = -moveSpeed;

		else if (state == AnimationState::RunRight)
			xMove = moveSpeed * 2;
		else if (state == AnimationState::WalkRight)
			xMove = moveSpeed;

		float xFrameMove = xMove;
		float yFrameMove = yMove;
		owner->transform->AddPosition(xFrameMove, yFrameMove);

		return;
	}

	bool left = input->IsKeyPressed(Input::Key::Left);
	bool right = input->IsKeyPressed(Input::Key::Right);
	bool up = input->IsKeyPressed(Input::Key::Up);
	bool down = input->IsKeyPressed(Input::Key::Down);

	if (left && collider->FindLeft(currentPosition) == -1) {
		animation->SetAnimationState(AnimationState::WalkLeft);
		currentPosition.x -= 32;
	}
	else if (left)
		animation->SetAnimationState(AnimationState::IdleLeft);

	else if (right && collider->FindRight(currentPosition) == -1) {
		animation->SetAnimationState(AnimationState::WalkRight);
		currentPosition.x += 32;
	}
	else if (right)
		animation->SetAnimationState(AnimationState::IdleRight);

	else if (up && collider->FindUp(currentPosition) == -1) {
		animation->SetAnimationState(AnimationState::WalkUp);
		currentPosition.y -= 32;
	}
	else if (up)
		animation->SetAnimationState(AnimationState::IdleUp);

	else if (down && collider->FindDown(currentPosition) == -1) {
		animation->SetAnimationState(AnimationState::WalkDown);
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