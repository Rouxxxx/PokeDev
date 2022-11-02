#include "c_pnj.h"

C_pnj::C_pnj(Object* owner)
	: Component(owner), moveSpeed(2), collider(nullptr), isMoving(false), reachPosition(), behavior(nullptr), waitingTime(0) {
}

void C_pnj::UpdateMove(float deltaTime, sf::Vector2f currentPosition) {
	AnimationState state = animation->GetAnimationState();

	if (isMoving)
		animation->StartUpdating();
	else
		animation->StopUpdating();

	if (isMoving && currentPosition == reachPosition) {
		collider->Delete(oldPosition);
		oldPosition = animToReachPosition(oldPosition, state);
		collider->Add(oldPosition, 2);
		isMoving = false;
		Update(deltaTime);
		return;
	}

	if (isMoving) {
		sf::Vector2f move = animToNewPosition(state, moveSpeed);
		owner->transform->AddPosition(move);

		return;
	}
	move(FacingDirection::Right, currentPosition);

}

void C_pnj::Update(float deltaTime) {
	sf::Vector2f currentPosition = owner->transform->GetPositionTrainer();
	UpdateSortOrder(currentPosition);

	if (hasBeenSpokenTo)
		return;

	(this->*(this->behavior))(deltaTime);
}


void C_pnj::UpdateSortOrder(sf::Vector2f currentPos) {
	int currSortOrder = spritePtr->GetSortOrder();
	int newSortOrder = (collider->playerAbove(currentPos.y)) ? 7 : 9;

	if (currSortOrder != newSortOrder) {
		spritePtr->SetSortOrder(newSortOrder);
		owner->GetDrawable()->SetSortOrder(newSortOrder);
		int res = _putenv("needTileSort=yes");
	}
}