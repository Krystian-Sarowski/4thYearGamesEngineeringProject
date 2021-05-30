#pragma once
#include <SFML/Graphics.hpp>
#include "VectorMath.h"

class Camera
{
private:

	sf::View m_cameraView;			//View used to display portion of the map.
	sf::RenderWindow& m_window;		//Window in which the view is active.

	sf::Vector2f m_cameraPos;		//Position of the view within the game world.
	
	float m_zoomLevel;				//The amount by which the window is zoomed in.

	void setCameraPos();

public:

	Camera(sf::RenderWindow& t_window);

	void moveCamera(sf::Vector2f t_mousePosition);
	void adjustZoom(float t_zoomAmount);
};

