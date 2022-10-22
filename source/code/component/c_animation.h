#pragma once
#include "component.h"
#include "../game/animation/animation.h"
#include "c_sprite.h"

enum AnimationState
{
	Idle = 0,
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
