#include "Worker.h"



Worker::Worker(ResourceManager * r, std::vector<Entity*> * e, Graph * g, int x, int y)
{
	m_position.x = x;
	m_position.y = y;

	m_graph = g;
	m_entity = e;

	m_resource = r;

	m_sprite = ManagedSprite(r->GetTexture("worker"), 16, 16);
	m_sprite.SetScale(2);

	m_sprite.SetIdle(0);
	m_sprite.SetAnimationStates(1, 2);

	m_sprite.GetSprite()->setOrigin(8, 8);
	m_sprite.SetAnimationStates(0, 1);
	m_sprite.AnimateOn();

	m_type = "Worker";

	m_pathRenewTimer = 0;

	m_speed = 0;
}

void Worker::Update(sf::Time t)
{
	if (m_pathRenewTimer <= 0)
	{
		for (int i = 0; i < m_entity->size(); i++)
		{
			m_path.clear();
			m_path.push_back(Node(((rand() % 2) - 1) + (int)(m_position.x / 32), ((rand() % 2) - 1) + (int)(m_position.y / 32), false));
			m_pathRenewTimer = 150;
		}
	}
	m_pathRenewTimer--;

	sf::Rect<int> holderThis = sf::Rect<int>(m_position.x, m_position.y, 32, 32);
	sf::Rect<int> holderOther = sf::Rect<int>((m_path.back().x * 32) - 8, (m_path.back().y * 32) - 8, 48, 48);

	if (holderThis.intersects(holderOther))
	{
		if (m_path.size() > 1)
		{
			m_path.pop_back();
		}
	}

	seekAndWander(sf::Vector2f(m_path.back().x * 32, m_path.back().y * 32), t);

	for (int i = 0; i < m_entity->size(); i++)
	{

	}

	m_position = m_position + (m_velocity * (float)t.asSeconds());

	if (GetMagnitude(m_velocity) > 0)
	{
		m_orientation = (atan2(m_velocity.y, m_velocity.x) * 180 / 3.14159265);
	}

	m_sprite.GetSprite()->setPosition(m_position);
	m_sprite.Update();
}

void Worker::Draw(sf::RenderWindow & r)
{
	m_sprite.GetSprite()->setRotation(m_orientation);
	r.draw(*m_sprite.GetSprite());
}

void Worker::seekAndWander(sf::Vector2f otherLoc, sf::Time t)
{
	float timetotarget = 0.05;

	float targetSpeed = 0;
	sf::Vector2f targetVelocity = sf::Vector2f(0, 0);

	if (GetMagnitude(otherLoc - m_position) < m_radiusStop)
	{
		targetSpeed = 0;
	}
	else if (GetMagnitude(otherLoc - m_position) > m_radiusSlow)
	{
		targetSpeed = m_maxspeed;
	}
	else
	{
		targetSpeed = m_maxspeed * (GetMagnitude(otherLoc - m_position) / m_radiusSlow);
	}

	targetVelocity = otherLoc - m_position;
	targetVelocity.x = targetVelocity.x / GetMagnitude(targetVelocity);
	targetVelocity.y = targetVelocity.y / GetMagnitude(targetVelocity);

	targetVelocity = targetVelocity * targetSpeed;

	sf::Vector2f m_linear = targetVelocity - m_velocity;
	m_linear = m_linear / timetotarget;

	if (GetMagnitude(m_linear) > m_maxaccel)
	{
		m_linear.x = m_linear.x / GetMagnitude(m_linear);
		m_linear.y = m_linear.y / GetMagnitude(m_linear);

		m_linear = m_linear * m_maxaccel;
	}

	m_velocity = m_velocity + (m_linear * (float)t.asSeconds());
	if (m_velocity.x > m_maxspeed)
	{
		m_velocity.x = m_maxspeed;
	}
	else if (m_velocity.x < -m_maxspeed)
	{
		m_velocity.x = -m_maxspeed;
	}

	if (m_velocity.y > m_maxspeed)
	{
		m_velocity.y = m_maxspeed;
	}
	else if (m_velocity.y < -m_maxspeed)
	{
		m_velocity.y = -m_maxspeed;
	}
}
