#pragma once

// Valeurs définissant la l'échelle de chaque simulation. 
constexpr float PX_PER_METER_COLLISIONS = 400.f;
constexpr float PX_PER_METER_BALLISTIC = 60.f;

// Taille des projectiles en mètres dans chacune des simulations.
constexpr float OBJECTS_RADIUS_COLLISIONS = 0.05f;
constexpr float OBJECTS_RADIUS_BALLISTIC = 0.3f;

// Masses maximales et minimales des projectiles
constexpr float MAX_OBJ_MASS = 2.f;
constexpr float MIN_OBJ_MASS = 0.2f;
constexpr float OBJ_MASS_INCREMENT = 0.04f;

// Nombre de billes dans la simulation de collisions (sans compter la bille du lanceur)
constexpr unsigned OBJECTS_COUNT = 4u;

// Multiplicateur de vitesse pour le lanceur de projectiles
constexpr float SLINGSHOT_SPEED_MULTIPLIER = 2.f;

// Force de gravité en m/s
constexpr float GRAVITY = 9.81f;

// Rayon en mètres de la cible dans la simulation de balistique
constexpr float TARGET_RAD = 0.3f;

// Constantes concernant les tailles de police à utiliser.
// Ces valeurs n'ont pas été choisies au hasard, si on choisit des valeurs différentes,
// on risque de se heurter à un problème graphique qui fait que le texte s'affichera mal.
constexpr unsigned BIG_TEXT = 60u;
constexpr unsigned MEDIUM_TEXT = 48u;
constexpr unsigned SMALL_TEXT = 36u;
constexpr unsigned TINY_TEXT = 20u;

// Texte du bouton de lancement/arrêt de la simulation
const std::string LAUNCH_BUTTON_TEXT = "Lancer";
const std::string STOP_BUTTON_TEXT = "Stop";
