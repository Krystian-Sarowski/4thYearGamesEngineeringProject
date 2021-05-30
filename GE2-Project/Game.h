#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include "ThreadPool.h"
#include "Algorithm.h"

class Game
{
private:

	void update(sf::Time dt);
	void processEvents();
	void render();
	void setupWorld(MapType t_mapType);
	void removeEnemies();
	bool spawnEnemy(int t_xIndex, int t_yIndex, float t_size);

	sf::RenderWindow m_window;		//Window in which all sprites are drawn.

	sf::View m_mapView;				//The view of the used for the world.

	Map m_map;						//The grid world in which all enemeis and player exist.
	Camera m_camera;				//Used to display porition of the gameworld.
	Player m_player;				//The player which is the target for all enemies.
	ThreadPool m_threadPool;		//Threadpool that controls all the threads within this project.
	std::vector<Enemy*> m_enemies;	//All the enemies in the gameworld.

public:

	Game();

	void start();
};