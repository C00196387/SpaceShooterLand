#ifndef MISSILE_H
#define MISSILE_H

#include "Entity.h"
#include "Explosion.h"

class Missile : public Entity
{
public:
	Missile(ResourceManager * r, std::vector<Entity*> * e, Explosion * explosion, int x, int y);
	~Missile() {};

	void Update(sf::Time t, std::vector<Structure*>* s);
	void Draw(sf::RenderWindow & r);
	std::string Type() { return m_type; };
	sf::Vector2f Position() { return m_position; };
	void Fire(int x, int y);
	void Health(int x) { m_health = x; };
	int Health() { return m_health; };

private:

	const float m_maxspeed = 50;
	const float m_maxAcceleration = 50.0f;

	Explosion * m_explosion;
	std::vector<Entity*>* m_entity;
	int m_timer;
	float m_rotation;
	float m_speed;

	void Seek(sf::Vector2f otherLoc, sf::Time t);

	float GetMagnitude(sf::Vector2f v)
	{
		float x = sqrt((v.x * v.x) + (v.y * v.y));
		return x;
	}

};
#endif
