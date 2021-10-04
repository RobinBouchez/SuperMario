#pragma once
class Texture;
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Draw() const;
	void Update(float elapsedSec);

private:
	Texture* m_pTexture;

};

