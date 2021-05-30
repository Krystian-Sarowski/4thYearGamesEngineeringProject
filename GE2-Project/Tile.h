#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <mutex>
#include "TravelData.h"

class Tile
{
private:

	static std::mutex s_globalMutex;	//Used to lock static variables of the tile while accessing.
	static float s_neighbourCost;		//The cost of travel to each of the neighbours.

	sf::Vector2f m_positon;				//The position of the tile within the world.

	bool m_isTraversable{ false };		//Bool for if the tile can be traversed or not.
	bool m_isOccupied{ false };			//Bool for if the tile is occupied by enemy or not.
	unsigned int m_usageMultiplier{ 1 };//Multipler applied for each enemy that has used this tile.

	std::mutex m_tileMutex;				//Used to lock the memebr data of the tile.

	float m_heuristicCost{ 0 };			//The estimated cost from this tile to the target.

	std::map<int, TravelData> m_travelData;	//Travel data of the enemy that has moved through this tile.
	std::vector<Tile*> m_neighbourList;		//Vector that contains all the neigbours of this tile.

public:

	Tile();

	void setPosition(sf::Vector2f t_position);
	void setIsTraversable(bool t_isTraversable);
	void setIsOccupied(bool t_isOccupied);
	void addPreviousTile(int t_enemyID, Tile* t_previousTile);
	void addPathCost(int t_enemyID, float t_pathCost);
	void addNeighbourTile(Tile* t_tile);
	void addIsVisted(int t_enemyID, bool t_isVisted);
	void setHeuristicCost(float t_heursiticCost);
	void removeEnemyData(int t_enemyID);

	bool getIsTraversable();
	bool getIsVisited(int t_enemyID);
	bool getIsOccupied();
	Tile* getPrevious(int t_enemyID);

	sf::Vector2f getPosition();
	float getHeuristicCost();
	float getPathCost(int t_enemyID);
	float getComparisonCost(int t_enemyID);

	std::vector<Tile*> getNeighbours();

	static void setNeighbourCost(float t_newNeighbourCost);
	static float getNeighbourCost();
};

//Used to compare the tiles within the priroity queue for AStar.
class TileCompare
{
private:

	int m_enemyID;	//ID of the enemy for which we are sorting the tiles.

public:

	TileCompare(int t_enemyID);

	bool operator()(Tile* t_tile1, Tile* t_tile2);
};