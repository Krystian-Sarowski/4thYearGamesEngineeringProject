#include "Game.h"

Game::Game() : 
	m_window{ sf::VideoMode{ 1000, 1000, 32 }, "GE2 Project" },
	m_camera(m_window),
	m_player(&m_map)
{
	std::srand(static_cast<unsigned>(time(NULL)));

	m_mapView.reset(sf::FloatRect(0, 0, 3000, 3000));
	m_window.setFramerateLimit(60);
	m_window.setView(m_mapView);
}

void Game::start()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);	//60 fps

	while (m_window.isOpen())
	{
		processEvents();								//As many as possible
		std::cout << static_cast<int>(1.0f / clock.getElapsedTime().asSeconds()) << std::endl;
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			
			processEvents();							//At least 60 fps
			update(timePerFrame);						//60 fps
		}
		render();										//As many as possible
	}
}

void Game::update(sf::Time dt)
{
	sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	m_camera.moveCamera(mousePos);

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->update(dt.asSeconds());
	}
	removeEnemies();
}

void Game::processEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
			}

			if (event.key.code == sf::Keyboard::Num1)
			{
				setupWorld(MapType::SMALL);
			}

			if (event.key.code == sf::Keyboard::Num2)
			{
				setupWorld(MapType::MEDIUM);
			}

			if (event.key.code == sf::Keyboard::Num3)
			{
				setupWorld(MapType::LARGE);
			}

			if (event.key.code == sf::Keyboard::X)
			{
				m_threadPool.cancelAll();
			}
		}

		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}

		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
			{
				m_camera.adjustZoom(event.mouseWheelScroll.y * event.mouseWheelScroll.delta);
			}
		}
	}
}

void Game::render()
{
	m_window.clear();
	m_map.render(m_window);
	m_player.render(m_window);

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->render(m_window);
	}

	m_window.display();
}

void Game::setupWorld(MapType t_mapType)
{
	if (m_threadPool.getIsEmpty() && m_threadPool.getWorkingThreads() == 0)
	{
		switch (t_mapType)
		{
		case MapType::SMALL:
			m_map.generateSmallMap();
			break;
		case MapType::MEDIUM:
			m_map.generateMediumMap();
			break;
		case MapType::LARGE:
			m_map.generateLargeMap();
			break;
		default:
			break;
		}

		m_player.spawnPlayer();
		m_map.setHeuristicCost(m_player.getOccupiedTile());
		m_enemies.clear();

		int count = 0;

		switch (t_mapType)
		{
		case MapType::SMALL:
			while (count != 5)
			{
				int xIndex = 20 + rand() % 8 - 4;
				int yIndex = 20 + rand() % 8 - 4;
				if (spawnEnemy(xIndex, yIndex, 90.0f))
				{
					count++;
				}
			}
			break;
		case MapType::MEDIUM:
			while (count != 50)
			{
				int xIndex = 80 + rand() % 16 - 8;
				int yIndex = 50 + rand() % 40 - 20;
				if (spawnEnemy(xIndex, yIndex, 25.0f))
				{
					count++;
				}
			}
			break;
		case MapType::LARGE:
			while (count != 500)
			{
				int xIndex = 900 + rand() % 100 - 50;
				int yIndex = 400 + rand() % 100 - 50;
				if (spawnEnemy(xIndex, yIndex, 2.0f))
				{
					count++;
				}
			}
			break;
		default:
			break;
		}

		for (int i = 0; i < m_enemies.size(); i++)
		{
			m_threadPool.addTask(std::bind(&Algorithm::aStar, m_enemies[i]->getCurrentTile(), m_player.getOccupiedTile(), m_enemies[i], &m_map));
		}		
	}
}

void Game::removeEnemies()
{
	m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(), [](Enemy* enemy)
	{
		return enemy->getKillMe();
	}), m_enemies.end());
}

bool Game::spawnEnemy(int t_xIndex, int t_yIndex, float t_size)
{
	if (!m_map.m_grid[t_xIndex][t_yIndex]->getIsOccupied() && m_map.m_grid[t_xIndex][t_yIndex]->getIsTraversable())
	{
		m_enemies.push_back(new Enemy(m_map.m_grid[t_xIndex][t_yIndex], t_size));
		return true;
	}

	return false;
}
