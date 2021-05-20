#pragma once

constexpr float PIXELS_PER_METER_IN_COLLISION_SIMULATION = 400.f;
constexpr float PIXELS_PER_METER_IN_BALLISTIC_SIMULATION = 60.f;

constexpr float OBJECTS_RADIUS_IN_METERS_IN_COLLISION_SIMULATION = 0.05f;
constexpr float OBJECTS_RADIUS_IN_METERS_IN_BALLISTIC_SIMULATION = 0.3f;

constexpr float MAX_OBJ_MASS = 2.f;
constexpr float MIN_OBJ_MASS = 0.2f;
constexpr float OBJ_MASS_INCREMENT = 0.04f;

constexpr unsigned OBJECTS_COUNT = 4u;

constexpr float SLINGSHOT_SPEED_MULTIPLIER = 2.f;
constexpr float GRAVITY = 9.81f;

constexpr unsigned OBJECTS_TRACE_HISTORY_LENGTH = 20u;
constexpr float OBJECTS_TIME_BETWEEN_TRACE_SAVE = 0.02f;

constexpr float TARGET_RADIUS_IN_METERS = 0.1f;

constexpr unsigned BIG_TEXT_SIZE = 60u;
constexpr unsigned MEDIUM_TEXT_SIZE = 48u;
constexpr unsigned SMALL_TEXT_SIZE = 36u;
constexpr unsigned TINY_TEXT_SIZE = 20u;

constexpr float WINDPICKER_RADIUS = 80.f;
constexpr float WINDPICKER_MAX_WIND_INTENSITY = 50.f;

constexpr float RHO = 1.225f; // kg/m^3 au niveau de la mer, à 15°C
constexpr float PI = ch::FLT_PI;
constexpr float SPHERE_DRAG_COEFFICIENT = 0.47f;

const std::string LAUNCHER_LAUNCH_BUTTON_TEXT = "Lancer";
const std::string LAUNCHER_STOP_BUTTON_TEXT = "Stop";

const std::string TARGET_HIT_TEXT = "Cible atteinte !";
const std::string TARGET_MISSED_TEXT = "Raté...";
