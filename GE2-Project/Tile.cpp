#include "Tile.h"

std::mutex Tile::s_globalMutex;
float Tile::s_neighbourCost = 0.0f;

Tile::Tile()
{
	m_positon = sf::Vector2f(-10.0f, -10.0f);
	m_isTraversable = true;
}

void Tile::setPosition(sf::Vector2f t_position)
{
	m_positon = t_position;
}

void Tile::setIsTraversable(bool t_isTraversable)
{
	m_isTraversable = t_isTraversable;
}

void Tile::setIsOccupied(bool t_isOccupied)
{
	m_isOccupied = t_isOccupied;
}

void Tile::addPreviousTile(int t_enemyID, Tile* t_previousTile)
{
	std::unique_lock<std::mutex> lock(m_tileMutex);
	m_travelData[t_enemyID].m_previous = t_previousTile;
}

void Tile::addPathCost(int t_enemyID, float t_pathCost)
{
	std::unique_lock<std::mutex> lock(m_tileMutex);
	m_travelData[t_enemyID].m_pathCost = t_pathCost;
}

void Tile::addNeighbourTile(Tile* t_tile)
{
	m_neighbourList.push_back(t_tile);
}

void Tile::addIsVisted(int t_enemyID, bool t_isVisted)
{
	std::unique_lock<std::mutex> lock(m_tileMutex);
	m_usageMultiplier++;
	m_travelData[t_enemyID].m_isVisited = t_isVisted;
}

void Tile::setHeuristicCost(float t_heursiticCost)
{
	m_heuristicCost = t_heursiticCost;
}

void Tile::removeEnemyData(int t_enemyID)
{
	std::unique_lock<std::mutex> lock(m_tileMutex);
	m_travelData.erase(t_enemyID);
}

bool Tile::getIsTraversable()
{
	std::unique_lock<std::mutex> lock(m_tileMutex);
	return m_isTraversable;
}

bool Tile::getIsVisited(int t_enemyID)
{
	std::unique_lock<std::mutex> lock(m_tileMutex);
	return m_travelData[t_enemyID].m_isVisited;
}

bool Tile::getIsOccupied()
{
	std::unique_lock<std::mutex> lock(m_tileMutex);
	return m_isOccupied;
}

Tile* Tile::getPrevious(int t_enemyID)
{
	std::unique_lock<std::mutex> lock(m_tileMutex);
	return m_travelData[t_enemyID].m_previous;
}

sf::Vector2f Tile::getPosition()
{
	std::unique_lock<std::mutex> lock(m_tileMutex);
	return m_positon;
}

float Tile::getHeuristicCost()
{
	std::unique_lock<std::mutex> lock(m_tileMutex);
	return m_heuristicCost;
}

float Tile::getPathCost(int t_enemyID)
{
	std::unique_lock<std::mutex> lock(m_tileMutex);
	return m_travelData[t_enemyID].m_pathCost;
}

float Tile::getComparisonCost(int t_enemyID)
{
	std::unique_lock<std::mutex> lock(m_tileMutex);
	return m_travelData[t_enemyID].m_pathCost + m_heuristicCost + getNeighbourCost() * m_usageMultiplier;
}

std::vector<Tile*> Tile::getNeighbours()
{
	std::unique_lock<std::mutex> lock(m_tileMutex);
	return m_neighbourList;
}

void Tile::setNeighbourCost(float t_newNeighbourCost)
{
	std::unique_lock<std::mutex> lock(s_globalMutex);
	s_neighbourCost = t_newNeighbourCost;
}

float Tile::getNeighbourCost()
{
	std::unique_lock<std::mutex> lock(s_globalMutex);
	return s_neighbourCost;
}

TileCompare::TileCompare(int t_enemyID) :
	m_enemyID(t_enemyID)
{
}

bool TileCompare::operator()(Tile* t_tile1, Tile* t_tile2)
{
	return t_tile1->getPathCost(m_enemyID) + t_tile1->getHeuristicCost() > t_tile2->getPathCost(m_enemyID) + t_tile2->getHeuristicCost();
}