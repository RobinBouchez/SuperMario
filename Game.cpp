#include "pch.h"
#include "Game.h"
#include "Texture.h"
#include <iostream>

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pTextureBackground = new Texture{ "Resources/Background.png" };
	m_StartLevel = new Level1();
}

void Game::Cleanup( )
{
	delete m_StartLevel;
	m_StartLevel = nullptr;
	delete m_pTextureBackground;
	m_pTextureBackground = nullptr;
}

void Game::Update( float elapsedSec )
{

	m_StartLevel->Update(elapsedSec);

	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );
	m_pTextureBackground->Draw();
	m_StartLevel->Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e ) 
{
	m_StartLevel->ProcessKeyDownEvent(e);
	switch (e.keysym.sym)
	{
	case SDLK_i:
		GameInfo();
		break;
	default:
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_StartLevel->ProcessKeyUpEvent(e);
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	m_StartLevel->ProcessMouseMotionEvent(e);
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	m_StartLevel->ProcessMouseDownEvent(e);
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	m_StartLevel->ProcessMouseUpEvent(e);
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::GameInfo()
{
	std::cout << "-- Game Controls --" << std::endl;
	std::cout << "Space-bar : jump " << std::endl;
	std::cout << "Left and Right arrow keys : walk left/right " << std::endl;
}