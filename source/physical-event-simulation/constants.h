#pragma once

constexpr float PIXELS_PER_METER = 300.f;
constexpr float M_OBJECTS_RADIUS = 0.1f;
constexpr float P_OBJECTS_RADIUS = M_OBJECTS_RADIUS * PIXELS_PER_METER;

constexpr float MAX_OBJ_MASS = 2.f;
constexpr float MIN_OBJ_MASS = 0.2f;
constexpr float OBJ_MASS_INCREMENT = 0.04f;

constexpr unsigned OBJECTS_COUNT = 10u;

constexpr float SLINGSHOT_SPEED_MULTIPLIER = 4.f;
constexpr float GRAVITY = 9.81f;
constexpr float GRAVITY_PIXELS = GRAVITY * PIXELS_PER_METER;

constexpr unsigned OBJECTS_TRACE_HISTORY_LENGTH = 10u;
constexpr float OBJECTS_TIME_BETWEEN_TRACE_SAVE = 0.01f;
