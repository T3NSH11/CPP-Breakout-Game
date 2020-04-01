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
	Tile sprites[100];
	sf::Texture bot;
	int counter = 0;
	int countercolr = 2;
	int countercolg = 2;
	int countercolb = 2;
	int intb = 0;
	int intr = 0;
	int intg = 0;
	sf::Sprite *m_backgroundSprite;
};
