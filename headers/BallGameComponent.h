#pragma once
#include "Rect.h"
#include "GameComponent.h"
#include "PaddleGameComponent.h"


class BallGameComponent : public GameComponent {
private:
	Rect bounds;
	Vector2 velocity;
	float speed;

	float pauseTimer;  
	bool isPaused;

	PaddleGameComponent* leftPaddle;
	PaddleGameComponent* rightPaddle;

	RectangleRenderer renderer;

	void PaddleCollision(PaddleGameComponent* paddle, int direction) {
		if (!paddle || !bounds.Intersects(paddle->GetBounds())) {
			return;
		}
		//!!!!
		velocity.x = direction * abs(velocity.x);  

		float hitPos = (bounds.position.y - paddle->GetBounds().position.y) /
			(paddle->GetBounds().size.y / 2);
		velocity.y = hitPos * speed;
		
	}

public:
	BallGameComponent(Game* game, Vector2 startPos, PaddleGameComponent* leftPaddle, PaddleGameComponent* rightPaddle) :
		GameComponent(game),
		bounds{ startPos, Vector2(0.05f, 0.05f) },
		velocity(1.5f, 1.0f), 
		speed(1.0f),
		leftPaddle(leftPaddle),
		rightPaddle(rightPaddle) {}

	void Initialize() override {
		renderer.Initialize(game);
	}

	void Update(float deltaTime) override {
		if (isPaused) {
			pauseTimer -= deltaTime;
			if (pauseTimer <= 0.0f) {
				isPaused = false;
			}
			return; 
		}


		bounds.position.x += velocity.x * deltaTime;
		bounds.position.y += velocity.y * deltaTime;

		if (bounds.Top() < -0.95f || bounds.Bottom() > 0.95f) {
			velocity.y *= -1;
		}

		PaddleCollision(leftPaddle, 1);
		PaddleCollision(rightPaddle, -1);


		if (bounds.Right() > 0.95f) {
			std::cout << "Left Player Scores!\n" << std::endl;
			ResetBall(1); 
		}
		if (bounds.Left() < -0.95f) {
			std::cout << "Right Player Scores!\n" << std::endl;
			ResetBall(-1);  
		}
	}

	void ResetBall(int direction) {
		bounds.position = Vector2(0, 0);
		velocity = Vector2(direction * speed, (rand() % 200 - 100.0f) / 100.0f); 

		isPaused = true;
		pauseTimer = 1.5f;
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