#pragma once
class Mario;
class Grid;
class Texture;

class Level1
{
public:
	Level1();
	~Level1();
	void Draw() const;
	void Update(float elapsedseconds);

	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
	Texture* m_pTexture;
	Mario* m_mario;
	Grid* m_Grid;

};

