#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Bullet.h"
#include "Cannon.h"
#include "Explosion.h"

class Player : public Entity
{
public:
	Player(ResourceManager * r, std::vector<Entity*> * e, Explosion * explosion, sf::View * cam, int x, int y);
	~Player() {};

	void Update(sf::Time t, std::vector<Structure*>* s);
	void Draw(sf::RenderWindow & r);
	std::string Type() { return m_type; };
	sf::Vector2f Position() { return m_position; };
	void Health(int x) { m_health = x; };
	int Health() { return m_health; };

private:

	void Controls();

	sf::View * m_camera;
	float m_speed;

	Explosion * m_explosion;

	Cannon * m_cannon;

	std::vector<Entity*> * m_entity;

};
#endif
