#include "Game.h"
#include "CelestialBodyGameComponent.h"
#include "OrbitalCameraGameComponent.h"

int main() {
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    Game game(L"Solar System", hInstance, 800, 800);

    CelestialBodyGameComponent* sun = new CelestialBodyGameComponent(
        &game, nullptr,
        3.5f,
        Vector4(1.0f, 0.9f, 0.3f, 1.0f),
        0.2f,
        Vector3(0, 1, 0),
        0.0f, 0.0f,
        Vector3(0, 1, 0)
    );
    game.components.push_back(sun);

    CelestialBodyGameComponent* mercury = new CelestialBodyGameComponent(
        &game, sun,
        0.4f,
        Vector4(0.7f, 0.6f, 0.5f, 1.0f),
        0.1f,
        Vector3(0, 1, 0),
        3.0f, 1.2f,
        Vector3(0, 1, 0)
    );
    game.components.push_back(mercury);


    CelestialBodyGameComponent* venus = new CelestialBodyGameComponent(
        &game, sun,
        0.6f,
        Vector4(1.0f, 0.7f, 0.4f, 1.0f),
        0.05f,
        Vector3(0, 1, 0),
        4.5f, 0.9f,
        Vector3(0, 1, 0)
    );
    game.components.push_back(venus);

    CelestialBodyGameComponent* earth = new CelestialBodyGameComponent(
        &game, sun,
        0.7f,
        Vector4(0.2f, 0.5f, 0.9f, 1.0f),
        1.0f,
        Vector3(0, 1, 0),
        6.0f, 0.8f,
        Vector3(0, 1, 0)
    );
    game.components.push_back(earth);

    CelestialBodyGameComponent* moon = new CelestialBodyGameComponent(
        &game, earth,
        0.2f,
        Vector4(0.7f, 0.7f, 0.7f, 1.0f),
        0.3f,
        Vector3(0, 1, 0),
        1.2f, 2.5f,
        Vector3(0, 1, 0),
        24
    );
    game.components.push_back(moon);


    CelestialBodyGameComponent* mars = new CelestialBodyGameComponent(
        &game, sun,
        0.55f,
        Vector4(0.9f, 0.3f, 0.1f, 1.0f),
        0.7f,
        Vector3(0, 1, 0),
        7.5f, 0.7f,
        Vector3(0, 1, 0)
    );
    game.components.push_back(mars);

    CelestialBodyGameComponent* phobos = new CelestialBodyGameComponent(
        &game, mars,
        0.12f,
        Vector4(0.5f, 0.4f, 0.3f, 1.0f),
        0.5f,
        Vector3(0, 1, 0),
        0.8f, 3.5f,
        Vector3(0, 1, 0),
        16
    );
    game.components.push_back(phobos);

    CelestialBodyGameComponent* deimos = new CelestialBodyGameComponent(
        &game, mars,
        0.1f,
        Vector4(0.4f, 0.4f, 0.4f, 1.0f),
        0.4f,
        Vector3(0, 1, 0),
        1.1f, 2.8f,
        Vector3(0, 1, 0),
        16
    );
    game.components.push_back(deimos);


    CelestialBodyGameComponent* jupiter = new CelestialBodyGameComponent(
        &game, sun,
        1.5f,
        Vector4(0.8f, 0.6f, 0.4f, 1.0f),
        1.2f,
        Vector3(0, 1, 0),
        12.0f, 0.4f,
        Vector3(0, 1, 0)
    );
    game.components.push_back(jupiter);

    CelestialBodyGameComponent* io = new CelestialBodyGameComponent(
        &game, jupiter,
        0.25f,
        Vector4(1.0f, 0.7f, 0.2f, 1.0f),
        0.8f,
        Vector3(0, 1, 0),
        1.5f, 1.8f,
        Vector3(0, 1, 0),
        24
    );
    game.components.push_back(io);

    CelestialBodyGameComponent* europa = new CelestialBodyGameComponent(
        &game, jupiter,
        0.22f,
        Vector4(0.7f, 0.8f, 0.9f, 1.0f),
        0.6f,
        Vector3(0, 1, 0),
        2.0f, 1.5f,
        Vector3(0, 1, 0),
        24
    );
    game.components.push_back(europa);


    CelestialBodyGameComponent* ganymede = new CelestialBodyGameComponent(
        &game, jupiter,
        0.28f,
        Vector4(0.6f, 0.6f, 0.5f, 1.0f),
        0.7f,
        Vector3(0, 1, 0),
        2.5f, 1.3f,
        Vector3(0, 1, 0),
        24
    );
    game.components.push_back(ganymede);


    CelestialBodyGameComponent* callisto = new CelestialBodyGameComponent(
        &game, jupiter,
        0.24f,
        Vector4(0.5f, 0.5f, 0.4f, 1.0f),
        0.5f,
        Vector3(0, 1, 0),
        3.0f, 1.1f,
        Vector3(0, 1, 0),
        24
    );
    game.components.push_back(callisto);


    CelestialBodyGameComponent* saturn = new CelestialBodyGameComponent(
        &game, sun,
        1.3f,
        Vector4(0.9f, 0.8f, 0.6f, 1.0f),
        1.1f,
        Vector3(0, 1, 0),
        15.0f, 0.35f,
        Vector3(0, 1, 0)
    );
    game.components.push_back(saturn);


    CelestialBodyGameComponent* titan = new CelestialBodyGameComponent(
        &game, saturn,
        0.3f,
        Vector4(0.8f, 0.7f, 0.5f, 1.0f),
        0.6f,
        Vector3(0, 1, 0),
        2.2f, 1.2f,
        Vector3(0, 1, 0),
        24
    );
    game.components.push_back(titan);


    CelestialBodyGameComponent* rhea = new CelestialBodyGameComponent(
        &game, saturn,
        0.18f,
        Vector4(0.7f, 0.7f, 0.7f, 1.0f),
        0.4f,
        Vector3(0, 1, 0),
        1.6f, 1.6f,
        Vector3(0, 1, 0),
        20
    );
    game.components.push_back(rhea);


    CelestialBodyGameComponent* uranus = new CelestialBodyGameComponent(
        &game, sun,
        1.0f,
        Vector4(0.6f, 0.8f, 0.9f, 1.0f),
        0.9f,
        Vector3(0, 1, 0),
        18.0f, 0.28f,
        Vector3(0, 1, 0)
    );
    game.components.push_back(uranus);


    CelestialBodyGameComponent* titania = new CelestialBodyGameComponent(
        &game, uranus,
        0.18f,
        Vector4(0.6f, 0.6f, 0.7f, 1.0f),
        0.4f,
        Vector3(0, 1, 0),
        1.4f, 1.4f,
        Vector3(0, 1, 0),
        20
    );
    game.components.push_back(titania);


    CelestialBodyGameComponent* oberon = new CelestialBodyGameComponent(
        &game, uranus,
        0.16f,
        Vector4(0.5f, 0.5f, 0.6f, 1.0f),
        0.3f,
        Vector3(0, 1, 0),
        1.8f, 1.2f,
        Vector3(0, 1, 0),
        20
    );
    game.components.push_back(oberon);


    CelestialBodyGameComponent* neptune = new CelestialBodyGameComponent(
        &game, sun,
        0.98f,
        Vector4(0.3f, 0.4f, 0.8f, 1.0f),
        0.85f,
        Vector3(0, 1, 0),
        21.0f, 0.24f,
        Vector3(0, 1, 0)
    );
    game.components.push_back(neptune);


    CelestialBodyGameComponent* triton = new CelestialBodyGameComponent(
        &game, neptune,
        0.2f,
        Vector4(0.7f, 0.8f, 0.9f, 1.0f),
        0.5f,
        Vector3(0, 1, 0),
        1.3f, 1.3f,
        Vector3(0, 1, 0),
        24
    );
    game.components.push_back(triton);


    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < 50; i++) {
        float angle = (float)(rand() % 360) * 3.14159f / 180.0f;
        float radius = 8.5f + (float)(rand() % 20) / 20.0f;
        float x = cos(angle) * radius;
        float z = sin(angle) * radius;
        float y = (float)(rand() % 20 - 10) / 20.0f;

        CelestialBodyGameComponent* asteroid = new CelestialBodyGameComponent(
            &game, sun,
            0.08f,
            Vector4(0.5f + (rand() % 50) / 100.0f,
                0.4f + (rand() % 40) / 100.0f,
                0.3f + (rand() % 30) / 100.0f, 1.0f),
            0.1f,
            Vector3(0, 1, 0),
            radius, 0.5f + (rand() % 30) / 100.0f,
            Vector3(0, 1, 0),
            8
        );

        asteroid->GetPosition();

        game.components.push_back(asteroid);
    }


    HRESULT hr = game.Initialize();
    if (FAILED(hr)) {
        MessageBox(nullptr, L"Failed to initialize game", L"Error", MB_OK);
        return 1;
    }

    game.Run();

    return 0;
}