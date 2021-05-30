#pragma once
#include <SFML/Graphics.hpp>

class VectorMath
{
public:

	static float magnitude(sf::Vector2f t_vector);
	static float distance(sf::Vector2f t_vector1, sf::Vector2f t_vector2);

	static sf::Vector2f unit(sf::Vector2f t_vector);

	static void normalize(sf::Vector2f& t_vector);
	
	static sf::Vector2f scale(sf::Vector2f t_vector, float t_scaler);
	static sf::Vector2f divide(sf::Vector2f t_vector, float t_diviser);

private:

	VectorMath();
};