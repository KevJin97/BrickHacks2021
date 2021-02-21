#pragma once
#include "AnimatedGameObject.h"
#include <limits>
#include <stdlib.h>
//#include "Tensor.hpp"

class Neural
{
	public:
		void update();
		Neural();
		void set(sf::Time* T, AnimatedGameObject* a, AnimatedGameObject* o, int ws);
	private:
		AnimatedGameObject* ai;
		AnimatedGameObject* op;
		float opPotential;
		int windowSize;
		sf::Vector2f velocity;
		sf::Vector2f gravity;
		sf::Vector2f n_speed;
		sf::Time* deltaT;
		int jumpCost;
		int numIterations;
};