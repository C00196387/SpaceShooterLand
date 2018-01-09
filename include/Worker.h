#ifndef WORKER_H
#define WORKER_H

#include "Entity.h"
#include "Graph.h"

class Worker: public Entity
{
public:
	Worker(ResourceManager * r, Graph * g, int x, int y);
	~Worker() {}
	void Update(sf::Time t);
	void Draw(sf::RenderWindow & r);

private:
	float m_wanderOffset, m_wanderRadius, m_wanderRate, m_wanderOrientation, m_waxAcc;
	const float m_maxSpeed = 100;
	const float m_maxAcc = 25.0f;

	float m_speed;
	float m_rotationSpeed;
	Graph * m_graph;
	std::vector<Node>m_path;

};
#endif