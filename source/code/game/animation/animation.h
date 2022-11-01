#pragma once

#include <vector>

struct FrameData {
	int id;
	int x; // x position of sprite in the sheet.
	int y; // y position of sprite in the sheet.
	int width;
	int height;
	float displayTimeSeconds; // How long to display the frame.
};

enum class FacingDirection {
	Down,
	Left,
	Right,
	Up
};


class Animation
{
public:
	Animation(FacingDirection direction);
	void AddFrame(int textureID, int x, int y, int width, int height, float frameTime);
	const FrameData* GetCurrentFrame() const;
	bool UpdateFrame(float deltaTime);
	void Reset();

	FacingDirection GetDirection() const;
private:
	void IncrementFrame();
	// Stores all frames for our animation.
	std::vector<FrameData> frames;
	// Current frame.
	int currentFrameIndex;
	// We use this to decide when to transition to the next frame.
	float currentFrameTime;
	FacingDirection direction;
};