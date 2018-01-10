#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player :
	public Entity
{
public:
	Player(ResourceManager * r, std::vector<Entity*> * e, sf::View * cam, int x, int y);
	~Player() {};

	void Update(sf::Time t);
	void Draw(sf::RenderWindow & r);
	std::string Type() { return m_type; };
	sf::Vector2f Position() { return m_position; };

private:

	void Controls();

	sf::View * m_camera;
	float m_speed;
	float m_orientation;

	std::vector<Entity*> * m_entity;

};
#endif
