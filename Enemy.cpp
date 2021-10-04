#include "pch.h"
#include "Enemy.h"
#include "Texture.h"

Enemy::Enemy()
{
	//m_pTexture = new Texture("");
}

Enemy::~Enemy()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Enemy::Draw() const
{

}

void Enemy::Update(float elapsedSec)
{
}
