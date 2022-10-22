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
	//std::cout << "showed on screen: (" << currentPosition.x << ", " << currentPosition.y << ")\n";
	//currentPosition.x -= 16;
	currentPosition.y += 8;
	//std::cout << "in game: (" << currentPosition.x << ", " << currentPosition.y << ")\n";
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

	if (input->IsKeyPressed(Input::Key::Left)) {
		animation->SetAnimationState(AnimationState::WalkLeft);
		if (collider->FindLeft(currentPosition) == -1)
			currentPosition.x -= 32;
	}
	else if (input->IsKeyPressed(Input::Key::Right)) {
		animation->SetAnimationState(AnimationState::WalkRight);
		if (collider->FindRight(currentPosition) == -1)
			currentPosition.x += 32;
	}

	else if (input->IsKeyPressed(Input::Key::Up)) {
		animation->SetAnimationState(AnimationState::WalkUp);
		if (collider->FindUp(currentPosition) == -1)
			currentPosition.y -= 32;
	}
	else if (input->IsKeyPressed(Input::Key::Down)) {
		animation->SetAnimationState(AnimationState::WalkDown);
		if (collider->FindDown(currentPosition) == -1)
			currentPosition.y += 32;
	}
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