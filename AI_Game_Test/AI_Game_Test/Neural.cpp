#include "Neural.hpp"

Neural::Neural()
{
	velocity.x = 0;
	velocity.y = 0;
	n_speed.x = 400;
	n_speed.y = 950;
	gravity.x = 0;
	gravity.y = 3000;
	jumpCost = 0;
	numIterations = 0;
}

void Neural::set(sf::Time* T, AnimatedGameObject* a, AnimatedGameObject* o, int ws)
{
	deltaT = T;
	ai = a;
	op = o;
	windowSize = ws;
}

void Neural::update()
{
	sf::Vector2f aiPos = ai->getPosition();
	sf::Vector2f opPos = op->getPosition();
	float aiPosX = aiPos.x;
	float opPosX = opPos.x;
	

	//Here's where we'd plug in the bounds for the Schrodinger equation for the diff eq solver
	//float distribution[] = fun stuff ya know
	
	//Pick a random point based on the probability distribution
	//float randNum = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
	//int index = 0;
	//while (randNum > 0)
	//{
	//	randnum -= distribution[index];
	//	if (randNum <= 0)
	//	{
	//		break;
	//	}
	//	++index;
	//}
	//float nextPixel = index;
	float nextPixel = 200; //Temporary, delete later

	//Determine whether to move left or right
	bool m_left = true;
	if (aiPosX < nextPixel)
	{
		m_left = false;
	}
	bool m_right = !m_left;

	//Figure out if a jump is necessary
	bool m_jump = false;
	if ((aiPosX <= opPosX && opPosX <= nextPixel) || (aiPosX >= opPosX && opPosX >= nextPixel))
	{
		float rand = 2 * (static_cast <float> (std::rand())) / static_cast <float> (RAND_MAX);
		if (int(rand) == 1)
		{
			m_jump = true;
		}
	}

	//Now, execute those actions into the game
	sf::Vector2f movement(0.0f, 0.0f);
	if (m_right)		//right walk
	{
		velocity.x = n_speed.x;
		movement.x = velocity.x * deltaT->asSeconds();
	}
	else if (m_left)		//left walk
	{
		velocity.x = -n_speed.x;
		movement.x = velocity.x * deltaT->asSeconds();
	}
	if (m_jump)		//jump when on the ground. doublejump bool locks jump function so is unusable
	{
		if (velocity.y == 0.0)
		{
			velocity.y = -n_speed.y;
			jumpCost += fmin(abs(aiPosX), abs(windowSize - aiPosX));
		}
	}
	if (velocity.y != 0.0)		//continuously falls regardless of button press
	{
		velocity.y += 3000 * deltaT->asSeconds();		//h > g, acceleration h
		movement.y = velocity.y * deltaT->asSeconds();
		if (ai->getPosition().y > 600)	//change later to platform
		{
			velocity.y = 0.0f;
		}
	}
	ai->move(movement);
	numIterations += 1;
}