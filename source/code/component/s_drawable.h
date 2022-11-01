#pragma once

#include <map>
#include "c_Drawable.h"
#include "../object/object.h"
#include "c_sprite.h"

class S_Drawable
{
public:
	void Add(std::vector<std::shared_ptr<Object>>& object);
	void ProcessRemovals();
	void Draw(Window& window);
private:
	void Add(std::shared_ptr<Object> object);
	void Sort();
	void SortPNJs();
	std::vector<std::shared_ptr<Object>> drawables;
	std::vector<std::shared_ptr<Object>>::iterator pnjBegin;
	std::vector<std::shared_ptr<Object>>::iterator pnjEnd;
	bool needSort;
	bool firstDraw = true;
};
