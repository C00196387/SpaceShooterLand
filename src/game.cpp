#include <SFML/Graphics.hpp>
#include <iostream>
#include "stdafx.h"

#include "ResourceManager.h"
#include "Player.h"
#include "Predator.h"
#include "Worker.h"
#include "Space.h"
#include "Graph.h"

int main()
{
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(600, 600), "SFML works!");

	sf::View *mainCamera = new sf::View(sf::FloatRect(0, 0, 600, 600));
	mainCamera->setCenter(300, 300);
	mainCamera->zoom(0.5);

	Graph * solidMap = new Graph();

	srand(time(NULL));

	ResourceManager Resources;
	Resources.LoadTexture(".\\resources\\Player.png", "player");
	Resources.LoadTexture(".\\resources\\Space1.png", "space1");
	Resources.LoadTexture(".\\resources\\Space2.png", "space2");
	Resources.LoadTexture(".\\resources\\Space3.png", "space3");
	Resources.LoadTexture(".\\resources\\Predator.png", "predator");
	Resources.LoadTexture(".\\resources\\Worker.png", "worker");

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

	entity->push_back(new Player(&Resources, entity, mainCamera, 50, 50));
	entity->push_back(new Predator(&Resources, entity, solidMap, 250, 220));
	entity->push_back(new Predator(&Resources, entity, solidMap, 280, 270));
	entity->push_back(new Predator(&Resources, entity, solidMap, 230, 270));
	entity->push_back(new Predator(&Resources, entity, solidMap, 210, 250));
	entity->push_back(new Worker(&Resources, entity, solidMap, 50, 100));
	std::cout << entity->size() << std::endl;

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
			for (int i = 0; i < spaceTiles.size(); i++)
			{
				spaceTiles.at(i)->Update();
			}
			for (int i = 0; i < entity->size(); i++)
			{
				entity->at(i)->Update(timeSinceLastUpdate);
			}
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
			//No More
			window->display();
			window->setView(*mainCamera);

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}