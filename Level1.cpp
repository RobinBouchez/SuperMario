#include "pch.h"
#include "Level1.h"
#include "Mario.h"
#include "Grid.h"
#include "Texture.h"

Level1::Level1()
{
	m_mario = new Mario();
	m_Grid = new Grid("Resources/Level1.txt");
	m_mario->SetPosition(m_Grid->PointOfCoordinate(1, 1));
}

Level1::~Level1()
{
	delete m_mario;
	m_mario = nullptr;
	delete m_Grid;
	m_Grid = nullptr;
}

void Level1::Draw() const
{
	m_mario->Draw();
	m_Grid->Draw();
}

void Level1::Update(float elapsedseconds)
{
	m_mario->Update(elapsedseconds);
	m_Grid->Update(elapsedseconds);
	m_Grid->Collision(m_mario);
	m_mario->SetIsOnGround(m_Grid->IsOnGround(m_mario));
}

void Level1::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_LEFT:
		//std::cout << "Left arrow key released\n";
		m_mario->moveLeft();
		break;
	case SDLK_RIGHT:
		//std::cout << "`Right arrow key released\n";
		m_mario->moveRight();
		break;
	case SDLK_SPACE:
		m_mario->jump();
		break;
	default:
		break;
	}
}

void Level1::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
		//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
	case SDLK_RIGHT:
		m_mario->stopMovement();
		break;
	case SDLK_SPACE:
		
		break;
	default:
		break;
	}
}

void Level1::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Level1::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
		//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Level1::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}
