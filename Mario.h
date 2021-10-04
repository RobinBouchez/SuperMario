#pragma once
#include "Vector2f.h"
class Texture;
class Mario
{
public:
	Mario();
	~Mario();
	void Update(float elapsed);
	void Draw() const;
	void moveRight();
	void moveLeft();
	void jump();
	void stopMovement();
	Rectf GetBounds() const;
	void SetVerticalDirection(float value);
	void SetHorizontalDirection(float value);
	void SetBounds(const Rectf& bounds);
	void SetIsOnGround(bool value);
	void SetPosition(const Point2f& pos);
	void AddScore( int score);
	enum class CharacterState
	{
		Idle = 0,
		Walking = 1,
		Jumping = 2,
		Crouching = 3,
	};

private:
	Texture* m_pTextureRunCycle;
	Texture* m_pTextureIdle;
	Texture* m_pTextureJump;
	float m_ImageHeight = 32;
	float m_ImageWidth = 16;
	int m_CurrentIndex = 0;
	float m_TextureTimer = 0;
	Rectf m_PosMario{0,0,56,68};
	Vector2f m_Direction;
	bool m_MoveIsPressed = false;
	float m_Speed = 500.0f;
	float m_JumpStrength = 5000.0f;
	bool m_isOnGround = false;
	int m_Score = 0;	
	int m_AmountOfRunSprites = 3;
	int m_AmountOfJumpSprites = 2;
	int m_AmountOfIdleSprites = 2;
	CharacterState m_CharacterState = CharacterState::Idle;
};

