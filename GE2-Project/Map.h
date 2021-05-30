#pragma once
#include "Tile.h"
#include <iostream>
#include <vector>
#include <list>
#include "VectorMath.h"
#include <queue>
#include <Enemy.h>
#include <mutex>

enum class MapType
{
	SMALL,
	MEDIUM,
	LARGE
};

class Map
{
private:

	int m_width{ 0 };					//The width of the map.
	int m_height{ 0 };					//The height of the map.

	MapType m_mapType{ MapType::SMALL };	//The size type of the map.

	sf::Sprite m_gridSprite;				//The sprite of the grid.

	sf::RectangleShape m_renderTile;		//The rectangleshape used to draw each tile.
	sf::RenderTexture m_mapTexture;			//The texture of the whole tile grid.

	sf::Vector2f m_offset;					//Offset between the tiles.
	std::list<std::pair<int, int>> m_neighbourDir;	//List of directions used to attach neighbours

	void generateMap(float t_tileSize, float t_outlineSize);
	void setupNeighbours(float t_tileOffset);
	void generateTexture();

	bool getIsOutOfBounds(int t_x, int t_y);

public:

	Map();

	std::vector<std::vector<Tile*>> m_grid;

	MapType getMapType();

	void generateSmallMap();
	void generateMediumMap();
	void generateLargeMap();

	void setHeuristicCost(Tile* t_targetTile);
	void removeEnemyData(int t_enemyID);
	void render(sf::RenderWindow& t_window);

	void clear();
};