#include "c_keyboardMovement.h"
#include "../object/object.h"

C_KeyboardMovement::C_KeyboardMovement(Object* owner)
	: Component(owner), moveSpeed(100) , input(nullptr)
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

	int xMove = 0;
	if (input->IsKeyPressed(Input::Key::Left)) {
		xMove = -moveSpeed;
		animation->SetAnimationDirection(FacingDirection::Left);
		animation->SetAnimationState(AnimationState::WalkLeft);
	}
	else if (input->IsKeyPressed(Input::Key::Right)) {
		xMove = moveSpeed;
		animation->SetAnimationDirection(FacingDirection::Right);
		animation->SetAnimationState(AnimationState::WalkRight);
	}

	int yMove = 0;
	if (input->IsKeyPressed(Input::Key::Up)) {
		yMove = -moveSpeed;
		animation->SetAnimationDirection(FacingDirection::Up);
		animation->SetAnimationState(AnimationState::WalkUp);
	}
	else if (input->IsKeyPressed(Input::Key::Down)) {
		yMove = moveSpeed;
		animation->SetAnimationDirection(FacingDirection::Down);
		animation->SetAnimationState(AnimationState::WalkDown);
	}

	if (xMove == 0 && yMove == 0)
		animation->SetAnimationState(AnimationState::Idle);

	float xFrameMove = xMove * deltaTime;
	float yFrameMove = yMove * deltaTime;
	owner->transform->AddPosition(xFrameMove, yFrameMove);
}

void C_KeyboardMovement::Awake() {
	animation = owner->GetComponent<C_Animation>();
}
