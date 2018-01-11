#include "Predator.h"



Predator::Predator(ResourceManager * r, std::vector<Entity*> * e, Graph * g, int x, int y)
{
	m_position.x = x;
	m_position.y = y;

	m_graph = g;
	m_entity = e;

	m_resource = r;

	m_sprite = ManagedSprite(r->GetTexture("predator"), 16, 16);
	m_sprite.SetScale(2);

	m_sprite.GetSprite()->setOrigin(8, 8);
	m_sprite.SetAnimationStates(0, 1);
	m_sprite.AnimateOn();

	m_isSlave = false;
	m_leader = false;

	m_type = "Predator";

	m_pathRenewTimer = 0;

	m_alive = true;

	m_speed = 0;
}

void Predator::Update(sf::Time t)
{
	if (m_pathRenewTimer <= 0 && !m_isSlave)
	{
		for (int i = 0; i < m_entity->size(); i++)
		{
			if (m_entity->at(i)->Type() == "Player")
			{
				if (DistanceFormula(m_entity->at(i)->Position(), m_position) > 32 * 5)
				{
					m_path = m_graph->Path((int)(m_entity->at(i)->Position().x / 32), (int)(m_entity->at(i)->Position().y / 32), (int)(m_position.x / 32), (int)(m_position.y / 32));
					m_seekingPlayer = false;
				}
			}
			else if (m_entity->at(i)->Type() == "Predator" && m_entity->at(i) != this)
			{
				if (DistanceFormula(m_entity->at(i)->Position(), m_position) < 160)
				{
					if (!m_entity->at(i)->m_isSlave && !m_entity->at(i)->m_leader && m_formation.size() < 3)
					{
						m_leader = true;
						m_formation.push_back(m_entity->at(i));
						m_formation.back()->m_isSlave = true;
						m_formation.back()->m_master = this;
						std::cout << "I have enslaved " << i << "!" << std::endl;
						m_seekingPlayer = false;
					}
				}
			}
			m_pathRenewTimer = 150;
		}
	}
	else if (!m_isSlave)
	{
		m_pathRenewTimer--;
	}

	if (m_leader)
	{
		int playerIndex = -1;
		bool attackPlayer = false;
		for (int i = 0; i < m_entity->size(); i++)
		{
			if (m_entity->at(i)->Type() == "Player")
			{
				playerIndex = i;
				if (DistanceFormula(m_entity->at(i)->Position(), m_position) < 32 * 5)
				{
					attackPlayer = true;
					break;
				}
			}
		}
		if (attackPlayer)
		{
			m_path.clear();
			m_path.push_back(Node((m_entity->at(playerIndex)->Position().x / 32) - 2, (m_entity->at(playerIndex)->Position().y / 32), false));
			bool slaveOne = false;
			bool slaveTwo = false;
			for (int i = 0; i < m_formation.size(); i++)
			{
				m_formation.at(i)->m_path.clear();
				if (!slaveOne)
				{
					m_formation.at(i)->m_path.push_back(Node((m_entity->at(playerIndex)->Position().x / 32) + 2, m_entity->at(playerIndex)->Position().y / 32, false));
					slaveOne = true;
				}
				else if (!slaveTwo)
				{
					m_formation.at(i)->m_path.push_back(Node((m_entity->at(playerIndex)->Position().x / 32), (m_entity->at(playerIndex)->Position().y / 32) + 2, false));
					slaveTwo = true;
				}
				else
				{
					m_formation.at(i)->m_path.push_back(Node((m_entity->at(playerIndex)->Position().x / 32), (m_entity->at(playerIndex)->Position().y / 32) - 2, false));
				}
			}
		}
		else
		{
			for (int i = 0; i < m_formation.size(); i++)
			{
				m_formation.at(i)->m_path.push_back(Node((m_position.x / 32), (m_position.y / 32), false));
			}
		}
	}

	if (m_path.size() > 0)
	{
		sf::Rect<int> holderThis = sf::Rect<int>(m_position.x, m_position.y, 32, 32);
		sf::Rect<int> holderOther = sf::Rect<int>((m_path.back().x * 32) - 8, (m_path.back().y * 32) - 8, 48, 48);

		if (holderThis.intersects(holderOther))
		{
			if (m_path.size() > 1)
			{
				m_path.pop_back();
			}
		}
		Pursue(sf::Vector2f(m_path.back().x * 32, m_path.back().y * 32), t);
	}

	for (int i = 0; i < m_entity->size(); i++)
	{
		if (m_entity->at(i) != this)
		{
			sf::Vector2f tempPos = m_position;
			tempPos.x = m_position.x + (m_velocity.x * (float)t.asSeconds());
			sf::Rect<int> tempRect1 = sf::Rect<int>(tempPos.x, tempPos.y, 32, 32);
			sf::Rect<int> tempRect2 = sf::Rect<int>(m_entity->at(i)->Position().x, m_entity->at(i)->Position().y, 32, 32);

			sf::Vector2f tempPos2 = m_position;
			tempPos2.y = m_position.y + (m_velocity.y * (float)t.asSeconds());
			sf::Rect<int> tempRect3 = sf::Rect<int>(tempPos2.x, tempPos2.y, 32, 32);
			sf::Rect<int> tempRect4 = sf::Rect<int>(m_entity->at(i)->Position().x, m_entity->at(i)->Position().y, 32, 32);
			if (tempRect1.intersects(tempRect2))
			{
				m_velocity.x = (m_velocity.x * -1) / 2;
				m_entity->at(i)->m_velocity.x = (m_velocity.x / 2) * -1;
			}
			else if (tempRect3.intersects(tempRect4))
			{
				m_velocity.y = (m_velocity.y * -1) / 2;
				m_entity->at(i)->m_velocity.y = (m_velocity.y/2) * -1;
			}
		}
	}

	m_position = m_position + (m_velocity * (float)t.asSeconds());

	m_orientation = (atan2(m_velocity.y, m_velocity.x) * 180 / 3.14159265);

	m_sprite.GetSprite()->setPosition(m_position);
	m_sprite.Update();
}

void Predator::Draw(sf::RenderWindow & r)
{
	m_sprite.GetSprite()->setRotation(m_orientation);
	r.draw(*m_sprite.GetSprite());
}

void Predator::Pursue(sf::Vector2f otherLoc, sf::Time t)
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
	if (GetMagnitude(m_velocity) > m_maxspeed)
	{
		m_velocity.x = m_velocity.x / GetMagnitude(m_velocity);
		m_velocity.y = m_velocity.y / GetMagnitude(m_velocity);
		m_velocity = m_velocity * m_maxspeed;
	}
}
