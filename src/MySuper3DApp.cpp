#include "Game.h"
#include "TriangleGameComponent.h"
#include "BackgroundGameComponent.h"
#include "RotatingTriangleGameComponent.h"
#include "PaddleGameComponent.h"
#include "WallGameComponent.h"
#include "BallGameComponent.h"
#include <iostream>

void exampleGame() {
    Game game(L"Pong - Classic Arcade Game", GetModuleHandle(nullptr), 800, 800);

    const float LEFT_BOUND = -0.9f;
    const float RIGHT_BOUND = 0.9f;
    const float TOP_BOUND = 0.9f;
    const float BOTTOM_BOUND = -0.9f;

    const float PADDLE_X_LEFT = -0.85f;
    const float PADDLE_X_RIGHT = 0.85f;


    PaddleGameComponent* leftPaddle = new PaddleGameComponent(
        &game,
        Vector2(PADDLE_X_LEFT, 0.0f),
        Keys::W,
        Keys::S,
        BOTTOM_BOUND,
        TOP_BOUND
    );

    PaddleGameComponent* rightPaddle = new PaddleGameComponent(
        &game,
        Vector2(PADDLE_X_RIGHT, 0.0f),
        Keys::Up,
        Keys::Down,
        BOTTOM_BOUND,
        TOP_BOUND
    );

    WallComponent* topWall = new WallComponent(&game, Vector2(0.0f, 0.95f));
    WallComponent* bottomWall = new WallComponent(&game, Vector2(0.0f, -0.95f));

    BallGameComponent* ball = new BallGameComponent(
        &game,
        Vector2(0.0f, 0.0f),
        leftPaddle,
        rightPaddle
    );

    game.components.push_back(leftPaddle);
    game.components.push_back(rightPaddle);
    game.components.push_back(topWall);
    game.components.push_back(bottomWall);
    game.components.push_back(ball);

    game.Initialize();
    game.Run();

    std::cout << "Game finished!\n";
}

int main() {
    exampleGame();
}

