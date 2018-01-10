#ifndef CANNON_H
#define CANNON_H

#include <math.h>
#include "Entity.h"
#include "Player.h"

class Cannon : public Entity
{

public:
	Cannon(ResourceManager * r, std::vector<Entity*> * e, int x, int y);
	~Cannon() {}
	void Update(sf::Time t);
	void Draw(sf::RenderWindow & r);
	std::string Type() { return m_type; };
	sf::Vector2f Position() { return m_position; };
	void Cannon::rotateToMouse(sf::RenderWindow & r, sf::View * view, int x, int y);

private:
	float m_angle;
	sf::Vector2i m_mouse;
	sf::Vector2f m_position;
	const float PI = 3.14159265;

	float m_dx;
	float m_dy;

	float m_rotation;


};
#endif
