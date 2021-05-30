#include "Algorithm.h"

void Algorithm::aStar(Tile* t_startTile, Tile* t_targetTile, Enemy* t_enemy, Map* t_map)
{
	int enemyID = t_enemy->getID();
	float neighbourCost = Tile::getNeighbourCost();

	TileCompare compare = TileCompare(enemyID);

	std::priority_queue<Tile*, std::vector<Tile*>, TileCompare> pq(compare);

	t_startTile->addPathCost(enemyID, 0);
	pq.push(t_startTile);
	t_startTile->addIsVisted(enemyID, true);

	while (!pq.empty() && pq.top() != t_targetTile)
	{
		for (Tile* &neighbour : pq.top()->getNeighbours())
		{
			if (neighbour == pq.top()->getPrevious(enemyID))
			{
				continue;
			}

			if (neighbour->getIsTraversable())
			{
				float childCost = neighbourCost + pq.top()->getPathCost(enemyID);

				if (childCost < neighbour->getPathCost(enemyID))
				{
					neighbour->addPathCost(enemyID, childCost);
					neighbour->addPreviousTile(enemyID, pq.top());
				}

				if (neighbour->getIsVisited(enemyID) == false)
				{
					pq.push(neighbour);
					neighbour->addIsVisted(enemyID, true);
				}
			}
		}

		pq.pop();
	}

	std::vector<Tile*> path;

	if (t_targetTile->getPrevious(enemyID) != nullptr)
	{
		Tile* pathTile = t_targetTile;

		while (pathTile != t_startTile && pathTile != nullptr)
		{
			path.push_back(pathTile);
			pathTile = pathTile->getPrevious(enemyID);
		}
	}

	t_enemy->setPath(path);
	t_map->removeEnemyData(enemyID);
}
