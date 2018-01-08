#include "Player.h"



Player::Player(ResourceManager * r, sf::View * cam, int x, int y)
{
	m_position.x = x;
	m_position.y = y;

	m_resource = r;

	m_sprite = ManagedSprite(r->GetTexture("player"), 16, 16);
	m_sprite.SetScale(2);

	m_sprite.SetIdle(0);
	m_sprite.SetAnimationStates(1, 2);

	m_sprite.GetSprite()->setOrigin(8, 8);

	m_speed = 0;

	m_camera = cam;
}

void Player::Update(sf::Time t)
{
	Controls();

	m_velocity.x = m_speed * cos(m_orientation / (180 / 3.14159265));
	m_velocity.y = m_speed * sin(m_orientation / (180 / 3.14159265));

	m_position.x = m_position.x + m_velocity.x * t.asSeconds();
	m_position.y = m_position.y + m_velocity.y * t.asSeconds();

	m_camera->setCenter(m_position.x, m_position.y);

	m_sprite.GetSprite()->setPosition(m_position);
	m_sprite.Update();
}

void Player::Draw(sf::RenderWindow & r)
{
	m_sprite.GetSprite()->setRotation(m_orientation);
	r.draw(*m_sprite.GetSprite());
}

void Player::Controls()
{
	bool isAccelerateOn = false;
	bool isButtonPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		isAccelerateOn = true;
		isButtonPressed = true;
		m_speed += 2.5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_speed > 0)
		{
			m_speed -= 5;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_orientation -= 4;
		isButtonPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_orientation += 4;
		isButtonPressed = true;
	}

	if (m_speed > 100)
	{
		m_speed = 100;
	}

	if (isButtonPressed)
	{
		m_sprite.AnimateOn();
	}
	else
	{
		m_sprite.AnimateOff();
	}

	if(!isAccelerateOn)
	{
		m_speed *= 0.95;
	}

	if (m_speed <= 0.4)
	{
		m_speed = 0;
	}
}