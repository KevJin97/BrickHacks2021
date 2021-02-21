#pragma once
#include "pch.h"
#include <SFML/Graphics.hpp>
#include "AnimatedGameObject.h"
#include "RegularGameObject.h"

class Game
{
	public:
		Game();
		void run();
		
	private:
		void update();
		void processEvents();
		void render();
		
		sf::RenderWindow m_window;
		sf::Time deltaT;
		
		AnimatedGameObject player1;
		AnimatedGameObject player2;
		//RegularGameObject map;

};