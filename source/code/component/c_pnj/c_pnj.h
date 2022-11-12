#pragma once

#include <ctime>
#include <functional>
#include <random>

#include "../component.h"
#include "../c_animation.h"
#include "../../windowManager/input.h"
#include "../../object/object.h"
#include "../../object/objectCollection.h"

#include "../../map/collider.h"


enum class pnjBehavior {
	IdleLeft,
	IdleRight,
	IdleUp,
	IdleDown,
	IdleAround,
	Multiple
};


inline pnjBehavior findPNJBehavior(std::string str) {
	std::vector<std::pair<std::string, pnjBehavior>> table{
		{"idleLeft", pnjBehavior::IdleLeft},
		{"idleRight", pnjBehavior::IdleRight},
		{"idleUp", pnjBehavior::IdleUp},
		{"idleDown", pnjBehavior::IdleDown},
		{"idleAround", pnjBehavior::IdleAround},
		{"moving", pnjBehavior::Multiple}
	};

	for (auto curr : table)
		if (curr.first == str)
			return curr.second;
	return pnjBehavior::IdleDown;
}



class C_pnj : public Component
{
public:
	C_pnj(Object* owner);
	void Awake() override;
	void Update(float deltaTime) override;

	void SetCollider(Collider* collider);
	void SetMovementSpeed(int moveSpeed);
	void SetOldPosition(float, float);
	void SetOldPosition(sf::Vector2f);
	
	void SetSpritePtr(std::shared_ptr<C_Sprite>);
	void SetBehavior(std::string str, std::vector<std::string> = std::vector<std::string>(), std::vector<float> = std::vector<float>());

private:
	bool move(FacingDirection);
	void UpdateMove(float);

	void movementLeft();
	void movementRight();
	void movementUp();
	void movementDown();

	void UpdateSortOrder();

	AnimationState GetAnimationState();
	void SetAnimationState(AnimationState state);
	int moveSpeed;
	bool isMoving = false;
	bool hasBeenSpokenTo = false;
	Collider* collider;
	std::shared_ptr<C_Animation> animation;
	std::shared_ptr<C_Sprite> spritePtr;
	sf::Vector2f reachPosition;
	sf::Vector2f oldPosition;
	float waitingTime;
	float currentWait;

	std::vector<bool(C_pnj::*) ()> functions;
	std::vector<float> waits;
	void (C_pnj::*behavior)();

	void fillActions(std::vector<std::string> strings);
	void MultipleActionsFunc();
	void Idle();
	void IdleAround();

	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();
	bool IdleLeftBool();
	bool IdleRightBool();
	bool IdleUpBool();
	bool IdleDownBool();

	void IdleLeft();
	void IdleRight();
	void IdleUp();
	void IdleDown();

	int currentActionId = 0;
	sf::Vector2f currentPosition;
};