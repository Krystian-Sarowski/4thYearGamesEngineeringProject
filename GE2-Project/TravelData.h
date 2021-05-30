#pragma once

class Tile;

struct TravelData
{
	Tile* m_previous;		//The pointer to the previous tile on the path.
	float m_pathCost;		//The travel cost to this tile.
	bool m_isVisited;		//Has tile tile been visited already.

	TravelData() : m_previous(nullptr),
		m_pathCost(std::numeric_limits<float>::max()),
		m_isVisited(false) {}
};

#include "Tile.h"