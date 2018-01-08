#ifndef PREDATOR_H
#define PREDATOR_H

#include "Entity.h"
#include "Graph.h"

class Predator :
	public Entity
{
public:
	Predator(ResourceManager * r, Graph * g, int x, int y);
	~Predator() {};

	void Update(sf::Time t);
	void Draw(sf::RenderWindow & r);

private:

	const float m_maxspeed = 100;
	const float m_maxAcceleration = 25.0f;

	float m_speed;
	float m_orientation;
	float m_distanceToRotation;
	float m_rotationSpeed;
	Graph * m_graph;
	std::vector<Node> m_path;

};
#endif