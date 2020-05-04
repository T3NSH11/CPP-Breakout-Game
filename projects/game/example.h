#pragma once
#include <vector>
#include "app.h"
#include "Tile.h"
#include <iostream>
#include <fstream>

class Example : public App
{
public:
	Example();
	virtual ~Example();
	virtual bool start();
	virtual void update(float deltaT);
	virtual void render();
	virtual void cleanup();
	static Example &inst();
	std::vector < sf::RectangleShape> lines;
	sf::RectangleShape playerblock;
	sf::RectangleShape borderleft;
	sf::RectangleShape borderright;
	sf::RectangleShape bordertop;
	sf::RectangleShape borderbottom;
	sf::CircleShape ball;
	sf::Text restarttext;
	sf::Text gameovertext;
	sf::Text restartinfo;
	sf::Font font;
	Tile sprites[100];
	sf::Sprite test;
	sf::Texture bot;
	int counter = 0;
	int restart = 0;
	float ballsx = 8.0f;
	float ballsy = 8.0f;
	sf::Sprite *m_backgroundSprite;
};
