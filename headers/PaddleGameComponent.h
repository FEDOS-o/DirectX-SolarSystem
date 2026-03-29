#pragma once
#include "Rect.h"
#include "GameComponent.h"
#include "RectRender.h"

class PaddleGameComponent : public GameComponent {

private:
	Rect bounds;
	float speed;
	Keys upKey;
	Keys downKey;
	float minY;
	float maxY;

	RectangleRenderer renderer;

public:
	PaddleGameComponent(Game* game, Vector2 startPos, Keys upKey, Keys downKey, float minY = -0.7f, float maxY = 0.7f) :
		GameComponent(game),
		bounds{ startPos, Vector2(0.05f, 0.25f) },
		speed(2.0f),
		upKey(upKey),
		downKey(downKey),
		minY(minY),
		maxY(maxY) {}

	void Initialize() override {
		renderer.Initialize(game);
	}

	void Update(float deltaTime) override {
		if (game->Input->IsKeyDown(upKey)) {
			bounds.position.y += speed * deltaTime;
		}

		if (game->Input->IsKeyDown(downKey)) {
			bounds.position.y -= speed * deltaTime;
		}


		float halfHeight = bounds.size.y / 2;
		if (bounds.position.y - halfHeight < minY) {
			bounds.position.y = minY + halfHeight;
		}
		if (bounds.position.y + halfHeight > maxY) {
			bounds.position.y = maxY - halfHeight;
		}
	}

	void Draw() override {
		renderer.DrawRect(game, bounds, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	Rect GetBounds() const {
		return bounds;
	}

	void DestroyResources() override {
		renderer.DestroyResources();
	}
};