#pragma once
#include "../../component/component.h"
#include "../../component/c_animation.h"
#include "../../windowManager/input.h"
#include "../../object/object.h"
#include "../../object/objectCollection.h"

#include "../../map/collider.h"
#include <stdlib.h>

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
private:
	void moveLeft(sf::Vector2f);
	void moveRight(sf::Vector2f);
	void moveUp(sf::Vector2f);
	void moveDown(sf::Vector2f);
	void SetAnimationState(AnimationState state);
	int moveSpeed;
	bool isMoving;
	Collider* collider;
	std::shared_ptr<C_Animation> animation;
	std::shared_ptr<C_Sprite> spritePtr;
	sf::Vector2f reachPosition;
	sf::Vector2f oldPosition;
};
