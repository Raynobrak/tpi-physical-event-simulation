#include "FadingText.h"
#include "constants.h"

constexpr float LABEL_ZONE_SIZE = 500.f;

FadingText::FadingText(ch::vec_t center, std::string text, float fadingTime) : 
    Label(ch::AABB(center.x - LABEL_ZONE_SIZE / 2.f, center.y - LABEL_ZONE_SIZE / 2.f, LABEL_ZONE_SIZE, LABEL_ZONE_SIZE), MEDIUM_TEXT_SIZE, text),
    timeLeft_(fadingTime),
    fadingTime_(timeLeft_)
{}

void FadingText::update(float dt) {
    float opacity = timeLeft_ / fadingTime_;
    auto alpha = opacity * 255;
    auto color = color_palette::LIGHT_FOREGROUND;
    color.a = alpha;
    setTextColor(color);

    timeLeft_ -= dt;
}

bool FadingText::hasDisappeared() const
{
    return timeLeft_ <= 0.f;
}
