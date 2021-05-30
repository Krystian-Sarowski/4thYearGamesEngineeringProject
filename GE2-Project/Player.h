#pragma once
#include "Map.h"

class Player
{
private:

	sf::Vector2f m_position;		//Position of the player within the world.
	sf::RectangleShape m_body;		//Body used to draw the player within the world.

	Tile* m_occupiedTile;			//Pointer to the tile that the player is currently occupying.
	Map* m_map;						//Pointer to the map in which the player exists.

public:

	Player(Map* t_map);

	void spawnPlayer();
	void render(sf::RenderWindow& t_window);

	Tile* getOccupiedTile();
};