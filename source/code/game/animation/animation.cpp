#include "animation.h"

Animation::Animation(FacingDirection direction)
	: frames(std::vector<FrameData>()), currentFrameIndex(0), currentFrameTime(0.f), direction(direction)
{ }


void Animation::AddFrame(int textureID, int x, int y, int width, int height, float frameTime) {
	FrameData data;
	data.id = textureID;
	data.x = x;
	data.y = y;
	data.width = width;
	data.height = height;
	data.displayTimeSeconds = frameTime;
	frames.push_back(data);
}

const FrameData* Animation::GetCurrentFrame() const {
	return (frames.size() > 0) ? &frames[currentFrameIndex] : nullptr;
}

bool Animation::UpdateFrame(float deltaTime)
{
	if (frames.size() == 0)
		return false;

	currentFrameTime += deltaTime;
	if (currentFrameTime >= frames[currentFrameIndex].displayTimeSeconds) {
		currentFrameTime = 0.f;
		IncrementFrame();
	}

	return true;
}
void Animation::IncrementFrame() {
	currentFrameIndex = (currentFrameIndex + 1) % frames.size();
}

void Animation::Reset() {
	currentFrameIndex = 0;
	currentFrameTime = 0.f;
}

FacingDirection Animation::GetDirection() const {
	return direction;
}
