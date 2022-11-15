#include "c_keyboard.h"
#include "../c_pnj/c_pnj.h"

std::shared_ptr<Object> FacingDirToObject(FacingDirection dir, Collider* collider, sf::Vector2f pos) {
	switch (dir) {
	case FacingDirection::Up:
		return collider->FindUp(pos);
	case FacingDirection::Down:
		return collider->FindDown(pos);
	case FacingDirection::Left:
		return collider->FindLeft(pos);
	case FacingDirection::Right:
		return collider->FindRight(pos);
	default:
		return nullptr;
	}
}

AnimationState GetPNJAnim(FacingDirection playerDir) {
	switch (playerDir) {
	case(FacingDirection::Down):
		return AnimationState::IdleUp;
	case(FacingDirection::Up):
		return AnimationState::IdleDown;
	case(FacingDirection::Left):
		return AnimationState::IdleRight;
	case(FacingDirection::Right):
		return AnimationState::IdleLeft;
	default:
		return AnimationState::IdleDown;
	}
}

void C_Keyboard::UpdateRelease(bool isAPressed) {
	if (!hasReleasedA && !isAPressed)
		hasReleasedA = true;
}

void C_Keyboard::UpdateInteractions(float deltaTime, sf::Vector2f currentPosition) {
	if (isMoving)
		return;

	bool isAPressed = input->IsKeyPressed(Key::A);
	UpdateRelease(isAPressed);

	if (!isAPressed || !hasReleasedA)
		return;

	if (isInteracting) {
		if (owner->IsTextBoxDone()) {
			soundFactory->StartSound(SoundEnum::Cursor);
			owner->DisableTextBox();
			hasReleasedA = false;
			SetInteracting(false);
		}
		return;
	}
	

	FacingDirection currentFacingDir = animToDir(GetAnimationState());
	std::shared_ptr<Object> obj = FacingDirToObject(currentFacingDir, collider, currentPosition);
	std::shared_ptr<C_pnj> pnj = (obj) ? obj->GetComponent<C_pnj>() : nullptr;
	if (!obj || !pnj || pnj->IsMoving())
		return;

	pnj->SetAnimationState(GetPNJAnim(currentFacingDir));

	pnj->SetInteracted();
	SetInteracting(true);
	hasReleasedA = false;
	owner->SetTextBoxString("Oh! Qu'il est beau, ton Sac!");
	owner->EnableTextBox();
}