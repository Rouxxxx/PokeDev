#include "c_animation.h"
#include "../object/object.h"

C_Animation::C_Animation(Object* owner) 
	: Component(owner), currentAnimation(AnimationState::Idle, nullptr)
{}
void C_Animation::Awake()
{
	sprite = owner->GetComponent<C_Sprite>();
}


#include <iostream>
void C_Animation::Update(float deltaTime)
{
	if (currentAnimation.first == AnimationState::Idle)
		return;

	/*const char* AnimationStateStr[] =
	{
		"Idle",
		"WalkRight",
		"WalkLeft",
		"WalkUp",
		"WalkDown",
		"RunRight",
		"RunLeft",
		"RunUp",
		"RunDown"
	};
	std::cout << AnimationStateStr[currentAnimation.first] << std::endl;*/

	bool newFrame = currentAnimation.second->UpdateFrame(deltaTime);
	if (newFrame) {
		const FrameData* data = currentAnimation.second->GetCurrentFrame();
		sprite->Load(data->id);
		sprite->SetTextureRect(data->x, data->y, data->width, data->height);
	}
}

void C_Animation::AddAnimation(AnimationState state, std::shared_ptr<Animation> animation) {
	auto inserted = animations.insert(std::make_pair(state, animation));
	if (currentAnimation.first == AnimationState::Idle)
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

void C_Animation::SetAnimationDirection(FacingDirection dir) {
	if (currentAnimation.first != AnimationState::Idle)
		currentAnimation.second->SetDirection(dir);
}
