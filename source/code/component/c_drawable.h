#pragma once
#include <SFML/Graphics.hpp>
#include "../windowManager/window.h"

class C_Drawable
{
public:
	C_Drawable();
	virtual ~C_Drawable();
	virtual void Draw(Window& window) = 0;
	void SetSortOrder(int order);
	int GetSortOrder() const;
private:
	int sortOrder;
};
