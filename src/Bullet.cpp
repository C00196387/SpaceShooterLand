#include "Bullet.h"



Bullet::Bullet(ResourceManager * r, std::vector<Entity*> * e, int x, int y, std::string source)
{
	m_position.x = x;
	m_position.y = y;

	m_entity = e;

	m_resource = r;

	m_sprite = ManagedSprite(r->GetTexture("bullet"), 16, 16);
	m_sprite.SetScale(2);

	m_sprite.SetIdle(0);
	m_sprite.SetAnimationStates(0, 1);
	m_sprite.AnimateOn();

	m_sprite.GetSprite()->setOrigin(8, 8);

	m_type = "Bullet";
	m_rotation = 0;
	m_alive = false;
}

void Bullet::Update(sf::Time t)
{
	if (m_alive)
	{
		if (m_timer <= 0)
		{
			m_alive = false;
		}
		else
		{
			m_timer--;
		}

		m_velocity.x = m_speed * cos(m_orientation / (180 / 3.14159265));
		m_velocity.y = m_speed * sin(m_orientation / (180 / 3.14159265));

		m_position.x = m_position.x + m_velocity.x * t.asSeconds();
		m_position.y = m_position.y + m_velocity.y * t.asSeconds();

		m_rotation++;
		m_sprite.Update();
	}
}

void Bullet::Draw(sf::RenderWindow & r)
{
	if (m_alive)
	{
		m_sprite.GetSprite()->setPosition(m_position);
		m_sprite.GetSprite()->setRotation(m_rotation);
		r.draw(*m_sprite.GetSprite());
	}
}

void Bullet::Fire(int x, int y, float speed, float direction)
{
	m_position.x = x;
	m_position.y = y;
	m_speed = speed;
	m_orientation = direction;
	m_alive = true;
	m_timer = 300;
}