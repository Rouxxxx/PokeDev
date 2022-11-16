#include "c_Camera.h"
#include "../object/object.h"

C_Camera::C_Camera(Object* owner) 
	: Component(owner), window(nullptr)
{ }

void C_Camera::LateUpdate(float deltaTime)
{
	if (window == nullptr)
		return;

	sf::View view = window->GetView();

	const sf::Vector2f& targetPos = owner->transform->GetPosition();
	view.setCenter(targetPos.x, targetPos.y);
	Config::windowCentreX = targetPos.x;
	Config::windowCentreY = targetPos.y;
	window->SetView(view);
}
void C_Camera::SetWindow(Window* gameWindow) {
	window = gameWindow;
}
