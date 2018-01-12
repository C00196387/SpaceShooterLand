#include "Player.h"

Player::Player(ResourceManager * r, std::vector<Entity*> * e, Explosion * explosion, sf::View * cam, int x, int y)
{
	m_position.x = x;
	m_position.y = y;

	m_explosion = explosion;

	m_entity = e;

	m_resource = r;

	m_sprite = ManagedSprite(r->GetTexture("player"), 16, 16);
	m_sprite.SetScale(2);

	m_sprite.SetIdle(0);
	m_sprite.SetAnimationStates(1, 2);

	m_sprite.GetSprite()->setOrigin(8, 8);

	m_speed = 0;

	m_type = "Player";

	m_cannon = new Cannon(r, e, explosion, x, y, "Player");
	m_cannon->FireRate(25);

	m_alive = true;

	m_camera = cam;

}

void Player::Update(sf::Time t)
{
	Controls();

	m_velocity.x = m_speed * cos(m_orientation / (180 / 3.14159265));
	m_velocity.y = m_speed * sin(m_orientation / (180 / 3.14159265));

	m_position.x = m_position.x + m_velocity.x * t.asSeconds();
	m_position.y = m_position.y + m_velocity.y * t.asSeconds();

	m_cannon->Position(m_position.x, m_position.y);
	m_cannon->Update(t);

	m_camera->setCenter(m_position.x, m_position.y);

	m_sprite.GetSprite()->setPosition(m_position);
	m_sprite.Update();
}

void Player::Draw(sf::RenderWindow & r)
{
	m_sprite.GetSprite()->setRotation(m_orientation);
	r.draw(*m_sprite.GetSprite());
	m_cannon->Draw(r);
}
void Player::Controls()
{
	bool isAccelerateOn = false;
	bool isButtonPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		isAccelerateOn = true;
		isButtonPressed = true;
		m_speed += 2.5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (m_speed > 0)
		{
			m_speed -= 5;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_orientation -= 4;
		isButtonPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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