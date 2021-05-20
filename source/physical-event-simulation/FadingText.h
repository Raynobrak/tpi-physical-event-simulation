#pragma once

#include "Label.h"

constexpr float DEFAULT_FADING_TIME = 3.f;

class FadingText : public Label {
public:

	FadingText(ch::vec_t center, std::string text, float fadingTime = DEFAULT_FADING_TIME);
	void update(float dt);
	bool hasDisappeared() const;
private:
	float timeLeft_;
	float fadingTime_;
};

