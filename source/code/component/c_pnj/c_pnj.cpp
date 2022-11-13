#include "c_pnj.h"

C_pnj::C_pnj(Object* owner)
	: Component(owner), moveSpeed(2), collider(nullptr), isMoving(false), reachPosition(), currentPosition(), behavior(nullptr), hasToWait(0.0f), waitingTime(0.0f) {
}

void C_pnj::Awake() {
	animation = owner->GetComponent<C_Animation>();
	reachPosition = owner->transform->GetPosition();
}

void C_pnj::Update(float deltaTime) {
	currentPosition = owner->transform->GetPositionPNJ();
	UpdateSortOrder();

	if (hasBeenSpokenTo)
		return;
	waitingTime += deltaTime;
	UpdateMove(deltaTime);
	if (isMoving)
		return;

	(this->*(this->behavior))();
}


void C_pnj::UpdateSortOrder() {
	int currSortOrder = spritePtr->GetSortOrder();
	int newSortOrder = (collider->playerAbove(currentPosition.y)) ? 7 : 9;

	if (currSortOrder != newSortOrder) {
		spritePtr->SetSortOrder(newSortOrder);
		owner->GetDrawable()->SetSortOrder(newSortOrder);
		int res = _putenv("needTileSort=yes");
	}
}

