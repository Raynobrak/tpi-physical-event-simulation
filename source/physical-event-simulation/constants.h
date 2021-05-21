#pragma once

constexpr float PX_PER_METER_COLLISIONS = 400.f;
constexpr float PX_PER_METER_BALLISTIC = 60.f;

constexpr float OBJECTS_RADIUS_COLLISIONS = 0.05f;
constexpr float OBJECTS_RADIUS_BALLISTIC = 0.3f;

constexpr float MAX_OBJ_MASS = 2.f;
constexpr float MIN_OBJ_MASS = 0.2f;
constexpr float OBJ_MASS_INCREMENT = 0.04f;

constexpr unsigned OBJECTS_COUNT = 4u;

constexpr float SLINGSHOT_SPEED_MULTIPLIER = 2.f;

constexpr float GRAVITY = 9.81f;

constexpr float TARGET_RAD = 0.1f;

constexpr unsigned BIG_TEXT = 60u;
constexpr unsigned MEDIUM_TEXT = 48u;
constexpr unsigned SMALL_TEXT = 36u;
constexpr unsigned TINY_TEXT = 20u;

const std::string LAUNCH_BUTTON_TEXT = "Lancer";
const std::string STOP_BUTTON_TEXT = "Stop";
