#include "c_pnj.h"

float generateRandomfloat(float low, float high) {
	return low + static_cast<float>(rand()) * static_cast<float>(high - low) / RAND_MAX;
}
int generateRandomInt(int low, int high) {
	return low + static_cast<int>(rand()) * static_cast<int>(high - low) / RAND_MAX;
}

void C_pnj::fillActions(std::vector<std::string> strings) {
	for (auto currentStr : strings) {
		if		(currentStr == "moveLeft")
			functions.push_back(&C_pnj::moveLeft);
		else if (currentStr == "moveRight")
			functions.push_back(&C_pnj::moveRight);
		else if (currentStr == "moveUp")
			functions.push_back(&C_pnj::moveUp);
		else if (currentStr == "moveDown")
			functions.push_back(&C_pnj::moveDown);

		else if (currentStr == "idleLeft")
			functions.push_back(&C_pnj::IdleLeftBool);
		else if (currentStr == "idleRight")
			functions.push_back(&C_pnj::IdleRightBool);
		else if (currentStr == "idleUp")
			functions.push_back(&C_pnj::IdleUpBool);
		else if (currentStr == "idleDown")
			functions.push_back(&C_pnj::IdleDownBool);
	}
}


AnimationState intToState(int integer, AnimationState oldAnim) {
	std::vector<AnimationState> anims = {
		AnimationState::IdleDown,
		AnimationState::IdleUp,
		AnimationState::IdleLeft,
		AnimationState::IdleRight,
	};
	for (int i = 0; i < anims.size(); i++) {
		if (oldAnim == anims.at(i)) {
			anims.erase(anims.begin() + i);
			break;
		}
	}

	switch (integer) {
	case 0:
		return anims.at(0);
	case 1:
		return anims.at(1);
	case 2:
		return anims.at(2);
	default:
		return AnimationState::IdleDown;
	}
}

void C_pnj::IdleAround() {
	if (currentWait < waitingTime)
		return;

	currentWait = 0.0f;
	waitingTime = generateRandomfloat(2, 4);
	SetAnimationState(intToState(generateRandomInt(0, 2), GetAnimationState()));
}

void C_pnj::MultipleActionsFunc() {
	if (currentWait < waitingTime)
		return;

	currentWait = 0.0f;
	if ((this->*(functions.at(currentActionId)))()) {
		waitingTime = waits.at(currentActionId);
		size_t size = (functions.size() < waits.size()) ? functions.size() : waits.size();
		currentActionId = (currentActionId + 1) % size;
	}
	else
		animation->StopUpdating();
}

void C_pnj::SetBehavior(std::string str, std::vector<std::string> strings, std::vector<float> floats) {
	pnjBehavior behaviorObj = findPNJBehavior(str);

	switch (behaviorObj) {
	case pnjBehavior::IdleLeft:
		behavior = &C_pnj::IdleLeft;
		break;
	case pnjBehavior::IdleRight:
		behavior = &C_pnj::IdleRight;
		break;
	case pnjBehavior::IdleUp:
		behavior = &C_pnj::IdleUp;
		break;
	case pnjBehavior::IdleDown:
		behavior = &C_pnj::IdleDown;
		break;


	case pnjBehavior::IdleAround:
		behavior = &C_pnj::IdleAround;
		break;

	case pnjBehavior::Multiple:
		behavior = &C_pnj::MultipleActionsFunc;
		fillActions(strings);
		waits = floats;
		break;
	}
}