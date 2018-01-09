#include "Worker.h"

Worker::Worker(ResourceManager * r, Graph * g, int x, int y)
{
	m_position.x = x;
	m_position.y = y;

	m_graph = g;

	m_resource = r;

	m_sprite = ManagedSprite(r->GetTexture("worker"), 16, 16);
	m_sprite.SetScale(2);

	m_sprite.SetIdle(0);

	m_sprite.GetSprite()->setOrigin(8, 8);

	m_path.push_back(Node(16, 21, false));

	m_speed = 0;
};

void Worker::Update(sf::Time t)
{
	m_speed = 30;
	m_wanderOrientation = (atan2(((m_path.back().y * 32) - 16) - m_position.y, ((m_path.back().x * 32) - 16) - m_position.x) * 180 / 3.14) - 90;

	sf::Rect<int> holderThis = sf::Rect<int>(m_position.x, m_position.y, 32, 32);

	sf::Rect<int>holderOther = sf::Rect<int>((m_path.back().x * 32) - 8, (m_path.back().y * 32) - 8, 48, 48);

	if (holderThis.intersects(holderOther))
	{
		if (m_path.size() > 0)
		{
			m_path.pop_back();
		}

	}

	m_velocity.x = m_speed * cos((m_wanderOrientation + rand()%6-5) + 90 / (180 / 3.14159265));
	m_velocity.y = m_speed * sin(m_wanderOrientation + rand() % 6 - 5) + 90 / (180 / 3.14159265);

	m_position.x = m_position.x + m_velocity.x * t.asSeconds();
	m_position.y = m_position.y + m_velocity.y * t.asSeconds();

	m_sprite.GetSprite()->setPosition(m_position);
	m_sprite.Update();
}

void Worker::Draw(sf::RenderWindow & r)
{
	m_sprite.GetSprite()->setRotation(m_wanderOrientation + 90);
	r.draw(*m_sprite.GetSprite());
}