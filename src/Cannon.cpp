#include "Cannon.h"

Cannon::Cannon(ResourceManager * r, std::vector<Entity*>* e, int x, int y)
{
	m_resource = r;

	m_sprite = ManagedSprite(r->GetTexture("cannon"), 8, 16);
	m_sprite.SetScale(2);

	m_sprite.SetIdle(0);
	m_sprite.SetAnimationStates(1, 2);

	m_sprite.GetSprite()->setOrigin(4, 0);

}

void Cannon::Update(sf::Time t)
{
	m_position.x = (m_sprite.GetSprite()->getGlobalBounds().left);
	m_position.y = (m_sprite.GetSprite()->getGlobalBounds().top);

	m_dx = m_position.x - m_mouse.x;
	m_dy = m_position.y - m_mouse.y;
	m_rotation = (atan2(m_dy, m_dx)) * 180 / PI;
	m_mouse = sf::Mouse::getPosition();
	m_sprite.GetSprite()->setRotation(m_rotation);
}

void Cannon::Draw(sf::RenderWindow & r)
{
	m_sprite.GetSprite()->setRotation(m_rotation);
	r.draw(*m_sprite.GetSprite());
}

