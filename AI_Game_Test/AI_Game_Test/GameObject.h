#pragma once
#include "pch.h"
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject() {};
	virtual bool load() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void setPosition(float x, float y) = 0;
	virtual void move(sf::Vector2f) = 0;

	virtual sf::Vector2f getPosition() const = 0;
	virtual float getHeight() const = 0;
	virtual float getWidth() const = 0;
	virtual void processEvents() = 0;
	virtual void handlePlayerInput(sf::Keyboard::Key key, bool isDown) = 0;
	virtual sf::Vector2f getGravity() const = 0;

	virtual void setfilepath(std::string) = 0;
	virtual void setWindow(sf::RenderWindow&) = 0;
	virtual void setTime(sf::Time&) = 0;
	virtual void setScale(float) = 0;
	virtual void setDamage(int, int) = 0;
	virtual void setSpeed(float, float, float, float) = 0;
	virtual void setGravity(float, float) = 0;
	virtual bool getFacing() = 0;

	virtual bool IsInBox(GameObject*) = 0;

protected:
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	bool m_valid;
	bool m_jump;
	bool m_crouch;
	bool m_left;
	bool m_right;
	bool m_melee;
	bool m_range;
	bool m_block;
	bool m_hit;

	bool doublejump[2];
	bool sprint[2];

	bool facing;

	sf::Keyboard::Key k_jump, k_crouch, k_left, k_right, k_melee, k_range, k_block;

	std::string filepath;		//set in Game constructor
	sf::RenderWindow *m_window;	//set in Game constructor
	sf::Time *deltaT;			//set in Game constructor
	/*
	sf::Time Buttonpress;
	sf::Time Buttonrelease;
	sf::Clock LRButton;
	sf::Clock Hold;
	*/
	sf::Vector2f velocity;
	sf::Vector2f gravity;
	sf::Vector2f n_speed;
	sf::Vector2f f_speed;

	int percentage;
	int meleedamage;
	int rangedamage;
};