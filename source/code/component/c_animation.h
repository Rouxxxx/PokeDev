#pragma once
#include "component.h"
#include "../game/animation/animation.h"
#include "c_sprite.h"

enum AnimationState
{
	Idle = 0,
	IdleLeft,
	IdleRight,
	IdleUp,
	IdleDown,
	WalkRight,
	WalkLeft,
	WalkUp,
	WalkDown,
	RunRight,
	RunLeft,
	RunUp,
	RunDown
};

class C_Animation : public Component
{
public:
	C_Animation(Object* owner);
	void Awake() override;
	void Update(float deltaTime) override;
	// Add animation to object. We need its state as well 
	// so that we can switch to it.
	void AddAnimation(AnimationState state, std::shared_ptr<Animation> animation);
	// Set current animation states.
	void SetAnimationState(AnimationState state);
	// Returns current animation state.
	const AnimationState& GetAnimationState() const;
	void StartUpdating();
	void StopUpdating();
private:
	bool ShouldUpdate = true;
	std::shared_ptr<C_Sprite> sprite;
	std::map<AnimationState, std::shared_ptr<Animation>> animations;
	// We store a reference to the current animation so we 
	// can quickly update and draw it.
	std::pair<AnimationState, std::shared_ptr<Animation>> currentAnimation;
};


inline sf::Vector2f animToReachPosition(sf::Vector2f vec, AnimationState state) {
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

inline sf::Vector2f facingToReachPosition(sf::Vector2f vec, FacingDirection dir) {
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

inline sf::Vector2f animToNewPosition(AnimationState state, int moveSpeed) {
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