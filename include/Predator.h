#ifndef PREDATOR_H
#define PREDATOR_H

#include "Entity.h"
#include "Graph.h"
#include "Player.h"

class Predator :
	public Entity
{
public:
	Predator(ResourceManager * r, std::vector<Entity*> * e, Explosion * explosion, Graph * g, int x, int y);
	~Predator() {};

	void Update(sf::Time t, std::vector<Structure*>* s);
	void Draw(sf::RenderWindow & r);
	std::string Type() { return m_type; };
	sf::Vector2f Position() { return m_position; };
	void Health(int x) { m_health = x; };
	int Health() { return m_health; };

private:

	const float m_maxspeed = 50;
	const float m_maxAcceleration = 25.0f;
	const float m_radiusStop = 0;
	const float m_radiusSlow = 0;
	const float m_maxaccel = 10;

	bool m_seekingPlayer;

	float m_speed;
	std::vector<Entity*>* m_entity;
	Explosion * m_explosion;

	Cannon * m_cannon;

	Graph * m_graph;

	int m_pathRenewTimer;

	void Pursue(sf::Vector2f otherLoc, sf::Time t);

	float GetMagnitude(sf::Vector2f v)
	{
		float x = sqrt((v.x * v.x) + (v.y * v.y));

		return x;
	}
	float DistanceFormula(sf::Vector2f v1, sf::Vector2f v2)
	{
		float x = sqrt(((v2.x - v1.x)*(v2.x - v1.x)) + ((v2.y - v1.y)*(v2.y - v1.y)));

		return x;
	}

};
#endif