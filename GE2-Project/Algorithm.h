#pragma once
#include "Map.h"

class Algorithm
{
public:

	static void aStar(Tile* t_startTile, Tile* t_targetTile, Enemy* t_enemy, Map* t_map);

private:

	Algorithm();

};