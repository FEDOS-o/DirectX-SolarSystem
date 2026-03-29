#pragma once
#include "Rect.h"
#include "GameComponent.h"

class WallComponent : public GameComponent {
private: 
	Rect bounds;
	
	RectangleRenderer renderer;

public:
	WallComponent(Game* game, Vector2 startPos) : GameComponent(game), bounds{ startPos, Vector2(1.9f, 0.05f) } {}

	void Initialize() override {
		renderer.Initialize(game);
	}

	void Draw() override {
		renderer.DrawRect(game, bounds, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	void DestroyResources() override {
		renderer.DestroyResources();
	}
};