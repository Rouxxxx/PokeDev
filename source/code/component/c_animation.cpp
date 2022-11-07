#include "c_animation.h"
#include "../object/object.h"

C_Animation::C_Animation(Object* owner) 
	: Component(owner), currentAnimation(AnimationState::Idle, nullptr)
{}
void C_Animation::Awake() {
	sprite = owner->GetComponent<C_Sprite>();
}


void C_Animation::Update(float deltaTime) {
	if (!ShouldUpdate && currentAnimation.first > AnimationState::IdleDown)
		return;

	bool newFrame = currentAnimation.second->UpdateFrame(deltaTime);
	if (newFrame) {
		const FrameData* data = currentAnimation.second->GetCurrentFrame();
		sprite->Load(data->id);
		sprite->SetTextureRect(data->x, data->y, data->width, data->height);
	}
}

void C_Animation::AddAnimation(AnimationState state, std::shared_ptr<Animation> animation) {
	auto inserted = animations.insert(std::make_pair(state, animation));
	if (currentAnimation.first == AnimationState::Idle || animations.empty())
		SetAnimationState(state);
}

void C_Animation::SetAnimationState(AnimationState state) {
	// We only set an animation of it is not already 
	// our current animation.
	if (currentAnimation.first == state)
		return;

	auto animation = animations.find(state);
	if (animation != animations.end()) {
		currentAnimation.first = animation->first;
		currentAnimation.second = animation->second;
		currentAnimation.second->Reset();
	}
}

const AnimationState& C_Animation::GetAnimationState() const {
	// Returns out current animation state. We can use this 
	// to compare the objects current state to a desired state.
	return currentAnimation.first;
}

void C_Animation::StartUpdating() {
	ShouldUpdate = true;
};
void C_Animation::StopUpdating() {
	ShouldUpdate = false;
};




sf::Vector2f animToReachPosition(sf::Vector2f vec, AnimationState state) {
	switch (state) {
	case (WalkDown): case (RunDown):
		vec.y += 32;
		break;
	case (WalkUp): case (RunUp):
		vec.y -= 32;
		break;
	case (WalkLeft): case (RunLeft):
		vec.x -= 32;
		break;
	case (WalkRight): case (RunRight):
		vec.x += 32;
		break;
	}
	return vec;
}

sf::Vector2f facingToReachPosition(sf::Vector2f vec, FacingDirection dir) {
	switch (dir) {
	case (FacingDirection::Down):
		vec.y += 32;
		break;
	case (FacingDirection::Up):
		vec.y -= 32;
		break;
	case (FacingDirection::Left):
		vec.x -= 32;
		break;
	case (FacingDirection::Right):
		vec.x += 32;
		break;
	}
	return vec;
}

sf::Vector2f animToNewPosition(AnimationState state, int moveSpeed) {
	sf::Vector2f vec(0, 0);

	switch (state) {
	case (WalkDown): case (RunDown):
		vec.y += 1;
		break;
	case (WalkUp): case (RunUp):
		vec.y -= 1;
		break;
	case (WalkLeft): case (RunLeft):
		vec.x -= 1;
		break;
	case (WalkRight): case (RunRight):
		vec.x += 1;
		break;
	}

	if (state == RunDown || state == RunUp || state == RunRight || state == RunLeft)
		vec *= 2.0f;

	vec *= moveSpeed / 1.0f;
	return vec;
}

FacingDirection animToDir(AnimationState state) {
	switch (state) {
	case (IdleLeft): case(WalkLeft): case(RunLeft):
		return FacingDirection::Left;
	case (IdleRight): case(WalkRight): case(RunRight):
		return FacingDirection::Right;
	case (IdleUp): case(WalkUp): case(RunUp):
		return FacingDirection::Up;
	case (IdleDown): case(WalkDown): case(RunDown):
		return FacingDirection::Down;
	default:
		return FacingDirection::Down;
	}
}