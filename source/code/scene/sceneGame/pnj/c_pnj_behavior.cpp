#include "c_pnj.h"

float generateRandomfloat(float low, float high) {
	return low + static_cast<float>(rand()) * static_cast<float>(high - low) / RAND_MAX;
}
int generateRandomInt(int low, int high) {
	return low + static_cast<int>(rand()) * static_cast<int>(high - low) / RAND_MAX;
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

void C_pnj::Idle(float deltaTime) {
}
void C_pnj::IdleAround(float deltaTime) {
	currentWait += deltaTime;
	if (currentWait >= waitingTime) {
		currentWait = 0.0f;
		waitingTime = generateRandomfloat(2, 4);
		SetAnimationState(intToState(generateRandomInt(0, 2), GetAnimationState()));
	}
}
void C_pnj::SetBehavior(std::string str) {
	pnjBehavior behaviorObj = findPNJBehavior(str);

	switch (behaviorObj) {
	case pnjBehavior::IdleLeft: case pnjBehavior::IdleRight: case pnjBehavior::IdleUp: case pnjBehavior::IdleDown:
		behavior = &C_pnj::Idle;
		break;

	case pnjBehavior::IdleAround:
		behavior = &C_pnj::IdleAround;
		break;
	}
}