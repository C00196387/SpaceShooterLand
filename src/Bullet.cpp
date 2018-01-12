#include "Bullet.h"



Bullet::Bullet(ResourceManager * r, std::vector<Entity*> * e, Explosion * explosion, int x, int y, std::string source)
{
	m_position.x = x;
	m_position.y = y;

	m_entity = e;
	m_explosion = explosion;

	m_resource = r;

	m_sprite = ManagedSprite(r->GetTexture("bullet"), 16, 16);
	m_sprite.SetScale(2);

	m_sprite.SetIdle(0);
	m_sprite.SetAnimationStates(0, 1);
	m_sprite.AnimateOn();

	m_sprite.GetSprite()->setOrigin(8, 8);

	m_source = source;

	m_explosion = explosion;

	m_type = "Bullet"; 
	m_rotation = 0;
	m_alive = false;
	m_health = 1; 
}

void Bullet::Update(sf::Time t)
{
	if (m_alive)
	{
		if (m_timer <= 0)
		{
			m_health = 0;
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

		for (int i = 0; i < m_entity->size(); i++)
		{
			sf::Vector2f tempPos = sf::Vector2f(m_position.x - 6, m_position.y - 6);
			sf::Rect<int> tempRect1 = sf::Rect<int>(tempPos.x, tempPos.y, 12, 12);
			sf::Rect<int> tempRect2 = sf::Rect<int>(m_entity->at(i)->Position().x - 16, m_entity->at(i)->Position().y - 16, 32, 32);
			if (tempRect1.intersects(tempRect2))
			{
				if (m_source == "Player")
				{
					if (m_entity->at(i)->Type() == "Predator" || m_entity->at(i)->Type() == "Nest")
					{
						m_entity->at(i)->Health(m_entity->at(i)->Health()-1);
						m_health = 0;
					}
				}
			}
		}
	}
	if (m_health <= 0 && m_alive)
	{
		m_explosionTimer = 120;
		m_alive = false;
	}
	else if (m_explosionTimer > 0 && !m_alive)
	{
		m_explosionTimer--;
	}
	else if (m_explosionTimer <= 0 && !m_alive)
	{
		m_position.x = -1000;
		m_position.y = -1000;
		m_sprite.GetSprite()->setPosition(m_position);
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
	if (m_explosionTimer > 0 && !m_alive)
	{
		m_explosion->m_position = m_position;
		m_explosion->Draw(r);
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
	m_health = 1;
}