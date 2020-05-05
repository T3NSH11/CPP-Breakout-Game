#pragma once
#include <SFML/Graphics.hpp>
class Tile
{
public:
	int id = 0;
	sf::Sprite sprite;
	int destroyed = 0;
};

