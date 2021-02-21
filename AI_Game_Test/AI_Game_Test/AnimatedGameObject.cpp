#pragma once
#include "AnimatedGameObject.h"
#include <iostream>
AnimatedGameObject::AnimatedGameObject()
{
	m_jump = false;
	m_crouch = false;
	m_left = false;
	m_right = false;
	m_melee = false;
	m_range = false;
	m_block = false;
	m_hit = false;
	doublejump[0] = false;
	doublejump[1] = true;
	sprint[0] = sprint[1] = false;

	velocity.x = 0;
	velocity.y = 0;

	k_jump	 =	sf::Keyboard::Up;
	k_crouch =	sf::Keyboard::Down;
	k_left   =	sf::Keyboard::Left;
	k_right	 =	sf::Keyboard::Right;
	k_melee  =	sf::Keyboard::P;
	k_range  =	sf::Keyboard::O;
	k_block  =	sf::Keyboard::I;

	int percentage = 0;
	meleedamage = 7;
	rangedamage = 3;

	n_speed.x = 400;	gravity.x = 0;
	n_speed.y = 950;	gravity.y = 3000;
	f_speed.x = 600;
	f_speed.y = 1200;

	//do this later make function to set later
	startpointx = 0;
	startpointy = 0;
	widthHalo = 145;
	heightHalo = 220;

	Animate.restart();
}

bool AnimatedGameObject::load()	//inital drawing
{
	if (m_texture.loadFromFile(filepath))
	{
		m_sprite.setTextureRect(sf::IntRect(startpointx, startpointy, widthHalo, heightHalo));	//initial sprite
		m_sprite.setTexture(m_texture);
		m_valid = true;
		return true;
	}
	else
	{
		return false;
	}
}

void AnimatedGameObject::draw()
{
	if (m_valid)
	{
		m_window->draw(m_sprite);
	}
}

void AnimatedGameObject::move(sf::Vector2f loc)
{
	if (m_valid)
	{
		GetAnimateTime = Animate.getElapsedTime();

		m_sprite.move(loc);
		if (loc.x == 0 && loc.y == 0)	//not moving, set not moving sprite
		{
			m_sprite.setTextureRect(sf::IntRect(startpointx, startpointy, widthHalo, heightHalo));
			m_sprite.setTexture(m_texture);
		}
		else if ((m_left || m_right) && loc.y == 0 && GetAnimateTime.asMilliseconds() >= 80)		//move left or right
		{
			Animate.restart();

			if (startpointx == (9 * widthHalo))
			{
				startpointx = 0;
			}
			startpointx += widthHalo;

			m_sprite.setTextureRect(sf::IntRect(startpointx, startpointy, widthHalo, heightHalo));
			m_sprite.setTexture(m_texture);
		}
	}
}

void AnimatedGameObject::processEvents()
{
	sf::Event event;
	m_window->pollEvent(event);
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
			
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		
		case sf::Event::Closed:
			m_window->close();
			break;
	}
}

void AnimatedGameObject::setInput(char c_jump, char c_crouch, char c_left, char c_right, char c_melee, char c_range, char c_block)
{
	int keytranslate[] = { c_jump, c_crouch, c_left, c_right, c_melee, c_range, c_block };
	sf::Keyboard::Key keys[] = { k_jump, k_crouch, k_left, k_right, k_melee, k_range, k_block };
	for (int i = 0; i < 7; i++)
	{
		if (keytranslate[i] >= 65 && keytranslate[i] <= 90)			//capital ASCII
		{
			keys[i] = (sf::Keyboard::Key)(keytranslate[i] - 65);
		}
		else if (keytranslate[i] >= 97 && keytranslate[i] <= 122)	//lowercase ASCII
		{
			keys[i] = (sf::Keyboard::Key)(keytranslate[i] - 97);
		}
		else if (keytranslate[i] >= 30 && keytranslate[i] <= 39)	//0 - 9
		{
			keys[i] = (sf::Keyboard::Key)(keytranslate[i] - 3);
		}
		else if (keytranslate[i] == ',')	keys[i] = sf::Keyboard::Key::Comma;
		else if (keytranslate[i] == '.')	keys[i] = sf::Keyboard::Key::Period;
		else if (keytranslate[i] == '/')	keys[i] = sf::Keyboard::Key::Slash;
		else if (keytranslate[i] == '\\')	keys[i] = sf::Keyboard::Key::Backslash;
		else if (keytranslate[i] == '[')	keys[i] = sf::Keyboard::Key::LBracket;
		else if (keytranslate[i] == ']')	keys[i] = sf::Keyboard::Key::RBracket;
		else if (keytranslate[i] == ';')	keys[i] = sf::Keyboard::Key::Semicolon;
		else if (keytranslate[i] == '-')	keys[i] = sf::Keyboard::Key::Dash;
		else if (keytranslate[i] == '=')	keys[i] = sf::Keyboard::Key::Equal;
		else if (keytranslate[i] == ' ')	keys[i] = sf::Keyboard::Key::Space;
		else if (keytranslate[i] == 1) { /*Empty Case. Leaves Keys as current */ }
		else if (keytranslate[i] == '\0')
		{
			switch (i)
			{
			case 0:
				keys[i] = sf::Keyboard::Key::Up;
				break;

			case 1:
				keys[i] = sf::Keyboard::Key::Down;
				break;

			case 2:
				keys[i] = sf::Keyboard::Key::Left;
				break;

			case 3:
				keys[i] = sf::Keyboard::Key::Right;
				break;

			case 4:
				keys[i] = sf::Keyboard::Key::P;
				break;

			case 5:
				keys[i] = sf::Keyboard::Key::O;
				break;

			case 6:
				keys[i] = sf::Keyboard::Key::I;
				break;
			}
		}
	}
	k_jump   = keys[0];
	k_crouch = keys[1];
	k_left   = keys[2];
	k_right  = keys[3];
	k_melee  = keys[4];
	k_range  = keys[5];
	k_block  = keys[6];
}

void AnimatedGameObject::handlePlayerInput(sf::Keyboard::Key key, bool isDown)
{
	if (key == k_left)
	{
		m_left = isDown;
		if (!isDown)
		{
			
		}
		else
		{
			
		}
	}
	else if (key == k_right)
	{
		m_right = isDown;
		if (!isDown)
		{
			
		}
		else
		{
			
		}
	}
	else if (key == k_jump)
	{
		m_jump = isDown;
	}
	else if (key == k_range)
	{
		m_range = isDown;
		if (isDown)
		{
			
		}
		else
		{
			
		}
	}
	else if (key == k_melee)
	{
		m_range = isDown;
		if (isDown)
		{
			
		}
		else
		{
			
		}
	}
	else if (key == k_block)
	{
		m_block = isDown;
	}
	else if (key == k_crouch)
	{
		m_crouch = isDown;
		if (isDown)
		{
			
		}
		else
		{
			
		}
	}
}

void AnimatedGameObject::update()
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (m_hit)
	{
		
	}
	else if (m_right && !sprint[0])		//right walk
	{
		velocity.x = n_speed.x;
		movement.x = velocity.x * deltaT->asSeconds();
		sprint[0] = true;
	}
	else if (!m_right && sprint[0])			//left sprint
	{
		if (Buttonrelease.asSeconds() <=0.25)
		{
			sprint[1] = true;
		}
		else
		{
			sprint[0] = false;
		}
	}
	else if (m_right && sprint[1])			//right sprint
	{
		velocity.x = f_speed.x;
		movement.x = velocity.x * deltaT->asSeconds();
	}
	if (velocity.x == 0.0)			//reset sprint bool
	{
		sprint[0] = ! (sprint[1] = true);
	} 
	else if (m_left && !sprint[0])		//left walk
	{
		velocity.x = -n_speed.x;
		movement.x = velocity.x * deltaT->asSeconds();
		sprint[0] = true;
	}
	else if (!m_left && sprint[0])		//left sprint set
	{
		if (Buttonrelease.asSeconds() <= 0.25)
		{
			sprint[1] = true;
		}
		else
		{
			sprint[0] = false;
		}
	}
	else if (m_left && sprint[1])			//left sprint
	{
		velocity.x = -f_speed.x;
		movement.x = velocity.x * deltaT->asSeconds();
	}
	if (m_jump)		//jump when on the ground. doublejump bool locks jump function so is unusable
	{
		if (velocity.y == 0.0)
		{
			velocity.y = -n_speed.y;
		}
		switch (doublejump[0] && doublejump[1])	//doublejump[0] is jump status, doublejump[1] is gate
		{
			case true:
				velocity.y = -n_speed.y;
				doublejump[1] = false;

			case false:
				velocity.y += gravity.y * deltaT->asSeconds();		//accerleration g
				break;
		}
	}
	else if (!m_jump && velocity.y != 0.0)		//prime doublejump when in mid air and not pressing up
	{
		if (doublejump[0] == false)	//if first jump is false
		{
			doublejump[0] = true;
		}
		velocity.y += 3000 * deltaT->asSeconds();		//h > g, acceleration h
	}

	if (m_block && velocity.y == 0.0f)
	{
		velocity.x = 0.0f;
	}
	if (m_crouch)
	{

	}
	if (velocity.y != 0.0)		//continuously falls regardless of button press
	{
		movement.y = velocity.y * deltaT->asSeconds();
		if (this->getPosition().y > 600)	//change later to platform
		{
			velocity.y = 0.0f;
			doublejump[0] = false;
			doublejump[1] = true;
		}
	}
	this->move(movement);
}

void AnimatedGameObject::setPosition(float x, float y)
{
	if (m_valid)
	{
		m_sprite.setPosition(x, y);
	}
}

sf::Vector2f AnimatedGameObject::getPosition() const
{
	if (m_valid)
	{
		return m_sprite.getPosition();
	}
	else
	{
		return sf::Vector2f(0, 0);
	}
}

float AnimatedGameObject::getHeight() const
{
	return m_sprite.getLocalBounds().height;
}

float AnimatedGameObject::getWidth() const
{
	return m_sprite.getLocalBounds().width;
}

void AnimatedGameObject::setfilepath(std::string path)			//use in Game constructor
{
	filepath = path;
}

void AnimatedGameObject::setWindow(sf::RenderWindow &temp)		//use in Game constructor
{
	m_window = &temp;
}

void AnimatedGameObject::setTime(sf::Time &dT)				//use in Game constructor
{
	deltaT = &dT;
}

void AnimatedGameObject::setScale(float scale)
{
	if (m_valid)
	{
		m_sprite.setScale(scale, scale);
	}
}

bool AnimatedGameObject::IsInBox(GameObject *other)
{
	float thiscorner[4][2] =
	{
		{ this->getPosition().x,							this->getPosition().y						},
		{ this->getPosition().x + this->getWidth(),			this->getPosition().y						},
		{ this->getPosition().x - this->getHeight(),		this->getPosition().y + this->getWidth()	},
		{ this->getPosition().x,							this->getPosition().y - this->getHeight()	}
	};
	float othercorner[4][2] =
	{
		{ other->getPosition().x,							other->getPosition().y						},
		{ other->getPosition().x + other->getWidth(),		other->getPosition().y						},
		{ other->getPosition().x + other->getWidth(),		other->getPosition().y - other->getHeight()	},
		{ other->getPosition().x,							other->getPosition().y - other->getHeight()	}
	};

	for (int i = 0; i < 4; i++)		//check if corners of other box is in this box
	{
		if (othercorner[i][0] <= thiscorner[0][0] && othercorner[i][0] >= thiscorner[2][0])	//check vertical sides
		{
			if (othercorner[i][1] <= thiscorner[0][1] && othercorner[i][1] >= thiscorner[2][1])	//check horizontal sides
			{
				return true;
			}
		}
	}
	for (int i = 0; i < 4; i++)		//just in case other object is larger, check if this box is inside other box
	{
		if (othercorner[0][0] >= thiscorner[i][0] && othercorner[2][0] <= thiscorner[i][0])	//check vertical sides
		{
			if (othercorner[0][1] >= thiscorner[i][1] && othercorner[2][1] <= thiscorner[i][1])	//check horizontal sides
			{
				return true;
			}
		}
	}
	return false;
}

void AnimatedGameObject::setDamage(int melee, int range)
{
	meleedamage = melee;
	rangedamage = range;
}

void AnimatedGameObject::setSpeed(float nx, float ny, float fx, float fy)
{
	n_speed.x = nx;
	n_speed.y = ny;
	f_speed.x = fx;
	f_speed.y = fy;
}

void AnimatedGameObject::setGravity(float gx, float gy)
{
	gravity.x = gx;
	gravity.y = gy;
}
