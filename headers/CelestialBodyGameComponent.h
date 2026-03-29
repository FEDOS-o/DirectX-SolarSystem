#pragma once
#include "GameComponent.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

class CelestialBody : public GameComponent {
protected:
    Vector3 position;
    Vector3 rotation;
    Vector3 rotationAxis;
    float rotationSpeed;

    float orbitRadius;
    float orbitSpeed;
    float orbitAngle;
    Vector3 orbitAxis;     // Ось орбитального вращения (X, Y или Z)

    Vector4 color;
    float size;

    CelestialBody* parent;

public:
    CelestialBody(Game* game, float size, const Vector4& color,
        float rotationSpeed = 1.0f,
        const Vector3& rotationAxis = Vector3(0, 1, 0),
        const Vector3& orbitAxis = Vector3(0, 1, 0)) : 
        GameComponent(game),
        position
    {

    }
};