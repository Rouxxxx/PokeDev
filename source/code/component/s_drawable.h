#pragma once

#include <map>
#include "c_Drawable.h"
#include "../object/object.h"

class S_Drawable
{
public:
	void Add(std::vector<std::shared_ptr<Object>>& object);
	void ProcessRemovals();
	void Draw(Window& window);
private:
	void Add(std::shared_ptr<Object> object);
	void Sort();
	std::vector<std::shared_ptr<Object>> drawables;
};
