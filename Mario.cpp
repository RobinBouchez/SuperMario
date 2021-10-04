#include "pch.h"
#include "Mario.h"
#include "Texture.h"

Mario::Mario()
{
	m_pTextureRunCycle = new Texture("Resources/RunCycle.png");
	m_pTextureIdle = new Texture("Resources/Idle.png");
	m_pTextureJump = new Texture("Resources/Jump.png");
	//m_ImageWidth = m_pTexture->GetWidth() / m_AmountColumns;
}

Mario::~Mario()
{
	delete m_pTextureRunCycle;
	m_pTextureRunCycle = nullptr;

	delete m_pTextureIdle;
	m_pTextureIdle = nullptr;

	delete m_pTextureJump;
	m_pTextureJump = nullptr;
}

void Mario::Update(float elapsed)
{
	m_CharacterState = CharacterState::Idle;
	
	//Movement
	if (m_MoveIsPressed)
	{
		m_PosMario.left += m_Direction.x * m_Speed * elapsed;
		m_CharacterState = CharacterState::Walking;
	}

	//Jump
	m_PosMario.bottom += m_Direction.y * elapsed;
	m_Direction.y -= 9.81f;
	if (m_isOnGround)
	{
		m_Direction.y = 0;	
	}
	else
	{
		m_CharacterState = CharacterState::Jumping;
	}

	m_TextureTimer += elapsed;
	switch (m_CharacterState)
	{
	case CharacterState::Idle:
		if (m_TextureTimer > 0.3f)
		{
			m_CurrentIndex++;
			m_CurrentIndex %= m_AmountOfIdleSprites;
			m_TextureTimer -= 0.3f;
		}
		break;
	case CharacterState::Walking:
		if (m_TextureTimer > 0.3f)
		{
			m_CurrentIndex++;
			m_CurrentIndex %= m_AmountOfRunSprites;
			m_TextureTimer -= 0.3f;
		}
		break;
	case CharacterState::Jumping:
		m_CurrentIndex = 0;

		break;
	case CharacterState::Crouching:
		m_CurrentIndex = 1;
		break;
	default:
		break;
	}
}

void Mario::Draw() const
{
	float imageSource = m_CurrentIndex * m_ImageWidth;
	switch (m_CharacterState)
	{
	case CharacterState::Walking:
		glPushMatrix();
		if (m_Direction.x > 0)
		{
			glTranslatef(m_PosMario.left, m_PosMario.bottom, 0);
			glScalef(-1, 1, 0);
			glTranslatef(-m_PosMario.left, -m_PosMario.bottom, 0);
		}
		m_pTextureRunCycle->Draw(m_PosMario, Rectf{ imageSource, 0, m_ImageWidth, m_ImageHeight });
		glPopMatrix();
		break;
	case CharacterState::Jumping:
	case CharacterState::Crouching:
		glPushMatrix();
		if (m_Direction.x < 0)
		{
			glTranslatef(m_PosMario.left, m_PosMario.bottom, 0);
			glScalef(-1, 1, 0);
			glTranslatef(-m_PosMario.left, -m_PosMario.bottom, 0);
		}
		m_pTextureJump->Draw(m_PosMario, Rectf{ imageSource, 0, m_ImageWidth, m_ImageHeight });
		glPopMatrix();
		break;
	case CharacterState::Idle:
	default:
		m_pTextureIdle->Draw(m_PosMario, Rectf{ imageSource, 0, m_ImageWidth, m_ImageHeight });
		break;
	}
}

void Mario::moveRight()
{
	if (m_MoveIsPressed == false)
	{
		m_MoveIsPressed = true;
		m_Direction = Vector2f(1, m_Direction.y);
	}
}

void Mario::moveLeft()
{
	if (m_MoveIsPressed == false)
	{
		m_MoveIsPressed = true;
		m_Direction = Vector2f(-1, m_Direction.y);
	}
}

void Mario::jump()
{
	if (m_isOnGround)
	{
		m_Direction.y = m_JumpStrength;
	}
}

void Mario::stopMovement()
{
	m_MoveIsPressed = false;
	m_Direction = Vector2f(0, 0);
}

Rectf Mario::GetBounds() const
{
	return m_PosMario;
}

void Mario::SetVerticalDirection(float value)
{
	m_Direction.y = value;
}

void Mario::SetHorizontalDirection(float value)
{
	m_Direction.x = value;
}

void Mario::SetBounds(const Rectf& bounds)
{
	m_PosMario = bounds;
}

void Mario::SetIsOnGround(bool value)
{
	m_isOnGround = value;
}

void Mario::SetPosition(const Point2f& pos)
{
	m_PosMario.left = pos.x;
	m_PosMario.bottom = pos.y;
}

void Mario::AddScore(int score)
{
	m_Score += score;
}
