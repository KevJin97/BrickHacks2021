#pragma once
#include "pch.h"
#include "GameObject.h"
#include <SFML\Graphics.hpp>

class RegularGameObject : public GameObject
{
	public:
		RegularGameObject() {}	//constructor
		bool load() {}
		void draw() {}
		void update() {}
		void setPosition(float x, float y) {}
		void move(sf::Vector2f) {}

		sf::Vector2f getPosition() const {}
		float getHeight() const {}
		float getWidth() const {}
		void processEvents() {}
		void handlePlayerInput(sf::Keyboard::Key key, bool isDown) {}

		void setInput(char c_jump, char c_crouch, char c_left, char c_right, char c_melee, char c_range, char c_block) {}
		void setfilepath(std::string) {}
		void setWindow(sf::RenderWindow&) {}
		void setTime(sf::Time&) {}
		void setScale(float) {}
		void setDamage(int melee, int range) {}
		void setSpeed(float, float, float, float) {}
		void setGravity(float, float) {}
		bool IsInBox(GameObject *other) {}

		void isHit(bool) {}

		bool getFacing() { return facing; }
		sf::Vector2f getGravity() const { return gravity; }

	private:
		bool facing;	//left = 0; right = 1
		sf::Time Buttonrelease;
};