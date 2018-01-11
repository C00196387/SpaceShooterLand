#include "Cannon.h"

Cannon::Cannon(ResourceManager * r, std::vector<Entity*>* e, int x, int y, std::string source)
{
	m_resource = r;

	m_position.x = x;
	m_position.y = y;

	m_sprite = ManagedSprite(r->GetTexture("cannon"), 8, 16);
	m_sprite.SetScale(2);

	m_sprite.SetIdle(0);
	m_sprite.SetAnimationStates(1, 2);

	m_sprite.GetSprite()->setOrigin(8, 8);

	m_source = source;

	for (int i = 0; i < 50; i++)
	{
		m_bullets.push_back(Bullet(r, e, m_position.x, m_position.y, source));
	}

	m_fireRate = 10;
	m_fireTimer = 0;
	m_bulletSpeed = 50;

}

void Cannon::Update(sf::Time t)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_source == "player" && m_fireTimer <= 0)
	{
		for (int i = 0; i < m_bullets.size(); i++)
		{
			if (!m_bullets.at(i).m_alive)
			{
				m_bullets.at(i).Fire(m_position.x + (10 * cos(m_orientation / (180 / 3.14))), m_position.y + (10 * sin(m_orientation / (180 / 3.14))), 100, m_orientation);
				m_fireTimer = m_fireRate;
				break;
			}
		}
	}
	if (m_fireTimer > 0)
	{
		m_fireTimer--;
	}
	if (m_source == "player")
	{
		m_dx = m_mouse.x - (m_position.x);
		m_dy = m_mouse.y - (m_position.y);
		m_orientation = (atan2(m_dy, m_dx)) * 180 / PI;
	}
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets.at(i).Update(t);
	}
}

void Cannon::Draw(sf::RenderWindow & r)
{
	m_mouse.x = (sf::Mouse::getPosition(r).x - 300)*10;
	m_mouse.y = (sf::Mouse::getPosition(r).y - 300)*10;
	m_sprite.GetSprite()->setPosition(m_position);
	m_sprite.GetSprite()->setRotation(m_orientation);
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets.at(i).Draw(r);
	}
	r.draw(*m_sprite.GetSprite());
}

void Cannon::ForceFire()
{
	if (m_fireTimer <= 0)
	{
		for (int i = 0; i < m_bullets.size(); i++)
		{
			if (!m_bullets.at(i).m_alive)
			{
				m_bullets.at(i).Fire(m_position.x + (10 * cos(m_orientation / (180 / 3.14))), m_position.y + (10 * sin(m_orientation / (180 / 3.14))), 100, m_orientation);
				m_fireTimer = m_fireRate;
				break;
			}
		}
	}
}