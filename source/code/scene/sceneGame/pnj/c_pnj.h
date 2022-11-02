#pragma once

#include <ctime>
#include <functional>
#include <random>

#include "../../component/component.h"
#include "../../component/c_animation.h"
#include "../../windowManager/input.h"
#include "../../object/object.h"
#include "../../object/objectCollection.h"

#include "../../map/collider.h"


enum class pnjBehavior {
	IdleLeft,
	IdleRight,
	IdleUp,
	IdleDown,
	IdleAround
};


inline pnjBehavior findPNJBehavior(std::string str) {
	std::vector<std::pair<std::string, pnjBehavior>> table{
		{"idleLeft", pnjBehavior::IdleLeft},
		{"idleRight", pnjBehavior::IdleRight},
		{"idleLeft", pnjBehavior::IdleUp},
		{"idleUp", pnjBehavior::IdleDown},
		{"idleAround", pnjBehavior::IdleAround}
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
	void SetCollider(Collider* collider);
	void UpdateSortOrder(sf::Vector2f);
	void SetMovementSpeed(int moveSpeed);
	void Update(float deltaTime) override;
	void UpdateMove(float, sf::Vector2f pos);
	void Awake() override;
	void SetIdle();
	void SetSpritePtr(std::shared_ptr<C_Sprite>);
	bool move(FacingDirection, sf::Vector2f);
	void SetOldPosition(float, float);
	void SetOldPosition(sf::Vector2f);
	void SetBehavior(std::string str);
private:
	void moveLeft(sf::Vector2f);
	void moveRight(sf::Vector2f);
	void moveUp(sf::Vector2f);
	void moveDown(sf::Vector2f);
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

	void (C_pnj::*behavior)(float);
	void Idle(float);
	void IdleAround(float);
};