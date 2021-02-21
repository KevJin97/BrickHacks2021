#include "pch.h"
#include "Game.h"

Game::Game() : m_window(sf::VideoMode(1440, 900), "Game Name")		//Change name
{
	player1.setfilepath("Build/MasterChiefOriginal1.png");
	player1.setTime(deltaT);
	player1.load();
	player1.setWindow(m_window);
	player1.setPosition(40, 600);
	player1.setScale(0.7f);
	player1.setInput(0, 0, 0, 0, '/', '.', ',');	
	//player1.setInput('w', 's', 'a', 'd', 'r', 't', 'y');
	
	player2.setfilepath("Build/PXL_20210206_032427276.jpg");
	player2.setTime(deltaT);
	player2.load();
	player2.setWindow(m_window);
	player2.setPosition(40, 600);
	player2.setScale(0.7f);
	//player2.setInput('w', 's', 'a', 'd', 'r', 't', 'y');
	neural.set(&deltaT, &player2, &player1, m_window.getSize().x);
}

void Game::run()
{
	sf::Clock clock;
	while (m_window.isOpen())
	{
		deltaT = clock.restart();
		processEvents();
		update();
		render();
	}
}

void Game::render()
{
	m_window.clear();
	player1.draw();
	player2.draw();
	
	m_window.display();
}

void Game::processEvents()
{
	player1.processEvents();
	//player2.processEvents();
	bool check = player1.IsInBox(&player2);
	if (check)
	{

	}
}

void Game::update()
{
	player1.update();
	//player2.update();
	neural.update();
}