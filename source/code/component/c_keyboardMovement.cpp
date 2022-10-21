#include "c_keyboardMovement.h"

C_KeyboardMovement::C_KeyboardMovement(Object* owner)
	: Component(owner), moveSpeed(1), input(nullptr), isMoving(false), reachPosition()
{}

void C_KeyboardMovement::SetInput(Input* input) {
	this->input = input;
}
void C_KeyboardMovement::SetMovementSpeed(int moveSpeed) {
	this->moveSpeed = moveSpeed;
}

void C_KeyboardMovement::Update(float deltaTime) {
	
	if (input == nullptr)
		return;

	sf::Vector2f currentPosition = owner->transform->GetPosition();
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

	isMoving = true;
	if (input->IsKeyPressed(Input::Key::Left)) {
		animation->SetAnimationDirection(FacingDirection::Left);
		animation->SetAnimationState(AnimationState::WalkLeft);
		currentPosition.x -= 32;
	}
	else if (input->IsKeyPressed(Input::Key::Right)) {
		animation->SetAnimationDirection(FacingDirection::Right);
		animation->SetAnimationState(AnimationState::WalkRight);
		currentPosition.x += 32;
	}

	else if (input->IsKeyPressed(Input::Key::Up)) {
		animation->SetAnimationDirection(FacingDirection::Up);
		animation->SetAnimationState(AnimationState::WalkUp);
		currentPosition.y -= 32;
	}
	else if (input->IsKeyPressed(Input::Key::Down)) {
		animation->SetAnimationDirection(FacingDirection::Down);
		animation->SetAnimationState(AnimationState::WalkDown);
		currentPosition.y += 32;
	}
	else {
		SetIdle();
		return;
	}
	
	reachPosition = currentPosition;

}

void C_KeyboardMovement::Awake() {
	animation = owner->GetComponent<C_Animation>();
}

void C_KeyboardMovement::SetIdle() {
	isMoving = false;
	animation->SetAnimationState(AnimationState::Idle);
}