#ifndef BORDER_H
#define BORDER_H

#include "Structure.h"
class Block : public Structure
{
public:
	Block(ManagedSprite* sprite, int x, int y, bool solid);
	~Block() {};

	void Update(sf::Time t) {};
	void Draw(sf::RenderWindow & r);

	bool Solid() { return m_solid; };

private:

	ManagedSprite * m_sprite;

};
#endif

