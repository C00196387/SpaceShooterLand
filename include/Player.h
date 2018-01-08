#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player :
	public Entity
{
public:
	Player(ResourceManager * r, sf::View * cam, int x, int y);
	~Player() {};

	void Update(sf::Time t);
	void Draw(sf::RenderWindow & r);

private:

	void Controls();

	sf::View * m_camera;
	float m_speed;
	float m_orientation;

};
#endif
