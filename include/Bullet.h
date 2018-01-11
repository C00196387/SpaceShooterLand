#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"
#include "Explosion.h"
class Bullet :
	public Entity
{
public:
	Bullet(ResourceManager * r, std::vector<Entity*> * e, Explosion * explosion, int x, int y, std::string source);
	~Bullet() {};

	void Update(sf::Time t);
	void Draw(sf::RenderWindow & r);
	std::string Type() { return m_type; };
	sf::Vector2f Position() { return m_position; };
	void Fire(int x, int y, float speed, float direction);
	void Health(int x) { m_health = x; };
	int Health() { return m_health; };

private:

	std::string m_source;
	Explosion * m_explosion;
	std::vector<Entity*> * m_entity;
	int m_timer;
	float m_rotation;
	float m_speed;
};

#endif

