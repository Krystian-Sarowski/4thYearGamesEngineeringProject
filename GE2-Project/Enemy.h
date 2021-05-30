#pragma once
#include "Tile.h"

class Enemy
{
private:

	static int s_nextID;						//The ID of the next enemy that will be created.

	int m_id;									//The ID of the enemy.

	const float m_MAX_MOVEMENT_DELAY{ 0.1f };	//The delay before which the enemy will move.

	float m_movemnetDelay{ 0.0f };				//The amount of time that has passed since last movement.

	bool m_killMe{ false };						//Should this enemy be destoryed or not.

	std::vector<Tile*> m_path;					//Path that the enemy uses to travel to the player. End of vector is the next tile.

	Tile* m_currentTile;						//The current tile that the enmy is occupying.

	sf::RectangleShape m_body;					//Body of the enemy used for rendering.

public:

	Enemy(Tile* t_startTile, float t_bodySize);
	void setPath(std::vector<Tile*> t_path);
	void update(float t_dt);
	void render(sf::RenderWindow& t_window);

	int getID();
	bool getKillMe();
	Tile* getCurrentTile();
};