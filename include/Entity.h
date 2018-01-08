#ifndef ENTITY_H
#define ENTITY_H

#include "stdafx.h"
#include "ResourceManager.h"
#include "ManagedSprite.h"

//All moving objects
class Entity
{
public:

	virtual void Update(sf::Time t) = 0;
	virtual void Draw(sf::RenderWindow & r) = 0;

	ResourceManager * m_resource;
	ManagedSprite m_sprite;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

};
#endif