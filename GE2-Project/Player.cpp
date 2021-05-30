#include "Player.h"

Player::Player(Map* t_map) :
	m_map(t_map),
	m_occupiedTile(nullptr)
{
	m_body.setFillColor(sf::Color::Magenta);
	m_body.setOutlineColor(sf::Color::Black);
}

void Player::spawnPlayer()
{
	int tileRange = 1;

	switch (m_map->getMapType())
	{
	case MapType::SMALL:
		m_body.setSize(sf::Vector2f(90.0f, 90.0f));
		tileRange = 5;
		break;
	case MapType::MEDIUM:
		m_body.setSize(sf::Vector2f(25.0f, 25.0f));
		tileRange = 10;
		break;
	case MapType::LARGE:
		m_body.setSize(sf::Vector2f(2.0f, 2.0f));
		tileRange = 30;
		break;
	default:
		break;
	}

	int x = rand() % tileRange;
	int y = rand() % tileRange;

	m_occupiedTile = m_map->m_grid[x][y];
	m_position = m_occupiedTile->getPosition();
	m_body.setPosition(m_position);
}

void Player::render(sf::RenderWindow& t_window)
{
	if (m_occupiedTile != nullptr)
	{
		t_window.draw(m_body);
	}
}

Tile* Player::getOccupiedTile()
{
	return m_occupiedTile;
}
