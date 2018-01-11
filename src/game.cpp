#include <SFML/Graphics.hpp>
#include <iostream>
#include "stdafx.h"

#include "ResourceManager.h"
#include "Player.h"
#include "Predator.h"
#include "Worker.h"
#include "Cannon.h"
#include "Space.h"
#include "Explosion.h"
#include "Graph.h"
#include "Missile.h"
#include "Nest.h"
#include "Radar.h"

int main()
{
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(600, 600), "SFML works!");

	sf::View *mainCamera = new sf::View(sf::FloatRect(0, 0, 600, 600));
	mainCamera->setCenter(300, 300);
	mainCamera->zoom(0.5);
	sf::View hudCamera = sf::View(sf::FloatRect(0, 0, 600, 600));
	hudCamera.zoom(0.5);
	hudCamera.setCenter(150, 150);
	Graph * solidMap = new Graph();
	srand(time(NULL));

	ResourceManager Resources;
	Resources.LoadTexture(".\\resources\\Player.png", "player");
	Resources.LoadTexture(".\\resources\\Space1.png", "space1");
	Resources.LoadTexture(".\\resources\\Space2.png", "space2");
	Resources.LoadTexture(".\\resources\\Space3.png", "space3");
	Resources.LoadTexture(".\\resources\\Predator.png", "predator");
	Resources.LoadTexture(".\\resources\\Worker.png", "worker");
	Resources.LoadTexture(".\\resources\\Cannon.png", "cannon");
	Resources.LoadTexture(".\\resources\\Bullet.png", "bullet");
	Resources.LoadTexture(".\\resources\\Explosion.png", "explosion");
	Resources.LoadTexture(".\\resources\\Missile.png", "missile");
	Resources.LoadTexture(".\\resources\\Nest.png", "nest");
	Resources.LoadTexture(".\\resources\\radar_none.png", "radar");
	Resources.LoadTexture(".\\resources\\radar_n.png",  "radar_n");
	Resources.LoadTexture(".\\resources\\radar_s.png",  "radar_s");
	Resources.LoadTexture(".\\resources\\radar_e.png",  "radar_e");
	Resources.LoadTexture(".\\resources\\radar_w.png",  "radar_w");
	Resources.LoadTexture(".\\resources\\radar_ne.png", "radar_ne");
	Resources.LoadTexture(".\\resources\\radar_nw.png", "radar_nw");
	Resources.LoadTexture(".\\resources\\radar_se.png", "radar_se");
	Resources.LoadTexture(".\\resources\\radar_sw.png", "radar_sw");


	std::vector<ManagedSprite*> spaceTiles;
	spaceTiles.push_back(new ManagedSprite(Resources.GetTexture("space1"), 16, 16));
	spaceTiles.at(0)->SetScale(2);
	spaceTiles.at(0)->SetAnimationStates(0, 1);
	spaceTiles.at(0)->AnimateOn();

	spaceTiles.push_back(new ManagedSprite(Resources.GetTexture("space2"), 16, 16));
	spaceTiles.at(1)->SetScale(2);
	spaceTiles.at(1)->SetAnimationStates(0, 1);
	spaceTiles.at(1)->AnimateOn();

	spaceTiles.push_back(new ManagedSprite(Resources.GetTexture("space3"), 16, 16));
	spaceTiles.at(2)->SetScale(2);
	spaceTiles.at(2)->SetAnimationStates(0, 1);
	spaceTiles.at(2)->AnimateOn();

	std::vector<std::vector<Space*>> space;

	for (int i = 0; i < 25; i++)
	{
		std::vector<Space*> holder;
		for (int j = 0; j < 25; j++)
		{
			holder.push_back(new Space(&spaceTiles, i, j));
			solidMap->AddNode(i, j, false);
		}
		space.push_back(holder);
	}

	solidMap->GenerateGraph();

	std::vector<Entity*> * entity = new std::vector<Entity*>();

	Explosion * explosion = new Explosion(&Resources, entity);

	entity->push_back(new Player(&Resources, entity, explosion, mainCamera, 0, 0));
	entity->push_back(new Worker(&Resources, entity, solidMap, 50, 100));
	//entity->push_back(new Nest(&Resources, entity, explosion, solidMap, 200, 300));
	//entity->push_back(new Nest(&Resources, entity, explosion, solidMap, 300, 300));
	//entity->push_back(new Nest(&Resources, entity, explosion, solidMap, 400, 300));

	Radar radar(&Resources, entity, 300-32,0);

	//FPS stuff
	sf::Clock clock;
	const float FPS = 60.0f;
	const sf::Time timePerFrame = sf::seconds(1.0f / FPS);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	clock.restart();
	//

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		
		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			//Logic Code Goes Here
			explosion->Position(sf::Vector2f(-1000, -1000));
			explosion->Update(timeSinceLastUpdate);
			for (int i = 0; i < spaceTiles.size(); i++)
			{
				spaceTiles.at(i)->Update();
			}
			for (int i = 0; i < entity->size(); i++)
			{
				entity->at(i)->Update(timeSinceLastUpdate);
			}
			radar.Update();
			//No More

			window->clear();
			//Display Code Goes Here
			for (int i = 0; i < space.size(); i++)
			{
				for (int j = 0; j < space.at(i).size(); j++)
				{
					space.at(i).at(j)->Draw(*window);
				}
			}
			for (int i = 0; i < entity->size(); i++)
			{
				entity->at(i)->Draw(*window);
			}
			window->setView(hudCamera);
			radar.Draw(*window);
			//No More
			window->display();
			window->setView(*mainCamera);

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}