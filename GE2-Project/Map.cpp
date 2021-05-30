#include "Map.h"

void Map::generateMap(float t_tileSize, float t_outlineSize)
{
	float tileOffset = t_tileSize + t_outlineSize * 2;

	m_renderTile.setSize(sf::Vector2f(t_tileSize, t_tileSize));
	m_renderTile.setOutlineThickness(t_outlineSize);
	m_renderTile.setOutlineColor(sf::Color::Black);

	for (int x = 0; x < m_width; x++)
	{
		std::vector<Tile*> col;

		for (int y = 0; y < m_height; y++)
		{
			col.push_back(new Tile());
			col[y]->setPosition(sf::Vector2f(tileOffset * x, tileOffset * y));
		}

		m_grid.push_back(col);
	}

	m_gridSprite.setPosition(0, 0);
}

void Map::setupNeighbours(float t_tileOffset)
{
	sf::Vector2f pos1 = sf::Vector2f(0, 0);
	sf::Vector2f pos2 = sf::Vector2f(t_tileOffset, t_tileOffset);

	Tile::setNeighbourCost(t_tileOffset);

	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			std::list<std::pair<int, int>>::iterator it;

			for (it = m_neighbourDir.begin(); it != m_neighbourDir.end(); ++it) 
			{
				std::pair<int, int> indexPos = std::pair<int, int>(x + it->first, y + it->second);

				if (!getIsOutOfBounds(indexPos.first, indexPos.second))
				{
					m_grid[x][y]->addNeighbourTile(m_grid[indexPos.first][indexPos.second]);
				}
			}
		}
	}
}

void Map::generateTexture()
{
	m_mapTexture.clear();

	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			m_renderTile.setPosition(m_grid[x][y]->getPosition());

			if (!m_grid[x][y]->getIsTraversable())
			{
				m_renderTile.setFillColor(sf::Color::Blue);
			}
			else
			{
				m_renderTile.setFillColor(sf::Color(105, 105, 105));
			}

			m_mapTexture.draw(m_renderTile);
		}
	}

	m_mapTexture.display();
	m_gridSprite.setTexture(m_mapTexture.getTexture());
}

void Map::removeEnemyData(int t_enemyID)
{
	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			m_grid[x][y]->removeEnemyData(t_enemyID);
		}
	}
}

bool Map::getIsOutOfBounds(int t_x, int t_y)
{
	if (t_x < 0 || t_x >= m_width)
	{
		return true;
	}
	else if(t_y < 0 || t_y >= m_height)
	{
		return true;
	}

	return false;
}

Map::Map()
{
	m_mapTexture.create(3000, 3000);
	m_renderTile.setPosition(sf::Vector2f(0, 0));

	m_neighbourDir.push_back(std::pair<int, int>(-1, 0));
	m_neighbourDir.push_back(std::pair<int, int>(0, -1));
	m_neighbourDir.push_back(std::pair<int, int>(1, 0));
	m_neighbourDir.push_back(std::pair<int, int>(0, 1));
}

void Map::generateSmallMap()
{
	clear();

	m_mapType = MapType::SMALL;
	m_width = 30;
	m_height = 30;
	
	generateMap(90.0f, 5.0f);

	for (int i = 0; i < 25; i++)
	{
		m_grid[14][i]->setIsTraversable(false);
		m_grid[15][i]->setIsTraversable(false);
	}

	for (int i = 3; i < 27; i++)
	{
		m_grid[6][i]->setIsTraversable(false);
		m_grid[7][i]->setIsTraversable(false);

		m_grid[21][i]->setIsTraversable(false);
		m_grid[22][i]->setIsTraversable(false);
	}

	generateTexture();
	setupNeighbours(100.0f);
}

void Map::generateMediumMap()
{
	clear();
	m_mapType = MapType::MEDIUM;
	m_width = 100;
	m_height = 100;

	generateMap(25.0f, 2.5f);

	for (int i = 30; i < 100; i++)
	{
		m_grid[30][i]->setIsTraversable(false);
		m_grid[31][i]->setIsTraversable(false);
	}

	for (int i = 0; i < 55; i++)
	{
		m_grid[70][i]->setIsTraversable(false);
		m_grid[71][i]->setIsTraversable(false);
	}

	for (int i = 10; i < 90; i++)
	{
		m_grid[15][i]->setIsTraversable(false);
		m_grid[16][i]->setIsTraversable(false);

		m_grid[43][i]->setIsTraversable(false);
		m_grid[44][i]->setIsTraversable(false);

		m_grid[55][i]->setIsTraversable(false);
		m_grid[56][i]->setIsTraversable(false);

		m_grid[82][i]->setIsTraversable(false);
		m_grid[83][i]->setIsTraversable(false);
	}

	generateTexture();
	setupNeighbours(30.0f);
}

void Map::generateLargeMap()
{
	clear();
	m_mapType = MapType::LARGE;
	m_width = 1000;
	m_height = 1000;

	generateMap(2.0f, 0.5f);

	for (int i = 0; i < 700; i++)
	{
		m_grid[60][i]->setIsTraversable(false);
		m_grid[61][i]->setIsTraversable(false);
	}

	for (int i = 0; i < 300; i++)
	{
		m_grid[500][i]->setIsTraversable(false);
		m_grid[501][i]->setIsTraversable(false);
	}

	for (int i = 400; i < 1000; i++)
	{
		m_grid[750][i]->setIsTraversable(false);
		m_grid[751][i]->setIsTraversable(false);
	}

	for (int i = 300; i < 600; i++)
	{
		m_grid[210][i]->setIsTraversable(false);
		m_grid[211][i]->setIsTraversable(false);

		m_grid[470][i]->setIsTraversable(false);
		m_grid[471][i]->setIsTraversable(false);

		m_grid[630][i]->setIsTraversable(false);
		m_grid[631][i]->setIsTraversable(false);

		m_grid[110][i]->setIsTraversable(false);
		m_grid[111][i]->setIsTraversable(false);

		m_grid[320][i]->setIsTraversable(false);
		m_grid[321][i]->setIsTraversable(false);
	}

	for (int i = 500; i < 900; i++)
	{
		m_grid[150][i]->setIsTraversable(false);
		m_grid[151][i]->setIsTraversable(false);

		m_grid[650][i]->setIsTraversable(false);
		m_grid[651][i]->setIsTraversable(false);

		m_grid[420][i]->setIsTraversable(false);
		m_grid[421][i]->setIsTraversable(false);

		m_grid[560][i]->setIsTraversable(false);
		m_grid[561][i]->setIsTraversable(false);

		m_grid[813][i]->setIsTraversable(false);
		m_grid[814][i]->setIsTraversable(false);
	}

	for (int i = 50; i < 500; i++)
	{
		m_grid[950][i]->setIsTraversable(false);
		m_grid[951][i]->setIsTraversable(false);

		m_grid[560][i]->setIsTraversable(false);
		m_grid[561][i]->setIsTraversable(false);

		m_grid[410][i]->setIsTraversable(false);
		m_grid[411][i]->setIsTraversable(false);

		m_grid[180][i]->setIsTraversable(false);
		m_grid[181][i]->setIsTraversable(false);

		m_grid[264][i]->setIsTraversable(false);
		m_grid[265][i]->setIsTraversable(false);
	}

	generateTexture();
	setupNeighbours(3.0f);
}

void Map::setHeuristicCost(Tile* t_targetTile)
{
	for (int col = 0; col < m_width; col++)
	{
		for (int row = 0; row < m_height; row++)
		{
			m_grid[col][row]->setHeuristicCost(VectorMath::distance(m_grid[col][row]->getPosition(), t_targetTile->getPosition()));
		}
	}
}

void Map::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_gridSprite);
}

void Map::clear()
{
	for (int x = m_width - 1; x >= 0; x--)
	{
		for (int y = m_height - 1; y >= 0; y--)
		{
			delete m_grid[x][y];
		}

		m_grid[x].clear();
	}

	m_grid.clear();
}

MapType Map::getMapType()
{
	return m_mapType;
}