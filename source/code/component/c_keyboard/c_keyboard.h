#pragma once
#include "../../component/component.h"
#include "../../component/c_animation.h"
#include "../../component/c_textbox.h"
#include "../../windowManager/input.h"
#include "../../object/object.h"

#include "../../map/collider.h"

class C_Keyboard : public Component
{
public:
	C_Keyboard(Object* owner);
	void SetInput(Input* input);
	void SetCollider(Collider* collider);
	void SetSoundFactory(SoundFactory*);

	void SetIdle();
	void SetInteracting(bool);
	void SetOldPosition(float, float);
	void SetOldPosition(sf::Vector2f);
	void SetMovementSpeed(int moveSpeed);

	void Update(float deltaTime) override;
	void KeysToMovement(sf::Vector2f);
	void Awake() override;
	bool isDirectionKeyPressed();
private:
	void UpdateRelease(bool);
	void UpdateInteractions(float, sf::Vector2f);
	void UpdateMovement(float, sf::Vector2f);
	AnimationState GetAnimationState();
	void SetAnimationState(AnimationState state);
	int moveSpeed;
	bool hasReleasedA = true;
	bool isMoving;
	bool isInteracting;
	Input* input;
	Collider* collider;
	SoundFactory* soundFactory;
	std::shared_ptr<C_Animation> animation;
	std::shared_ptr<C_TextBox> textBox;
	sf::Vector2f reachPosition;
	sf::Vector2f oldPosition;
};
