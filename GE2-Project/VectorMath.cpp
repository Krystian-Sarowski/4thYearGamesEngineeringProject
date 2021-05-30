#include "VectorMath.h"

float VectorMath::magnitude(sf::Vector2f t_vector)
{
    return sqrt(powf(t_vector.x, 2) + powf(t_vector.y, 2));
}

float VectorMath::distance(sf::Vector2f t_vector1, sf::Vector2f t_vector2)
{
    return sqrt(powf(t_vector2.x - t_vector1.x, 2) + powf(t_vector2.x - t_vector1.y, 2));
}

sf::Vector2f VectorMath::unit(sf::Vector2f t_vector)
{
    sf::Vector2f unitVector;

    float mag = magnitude(t_vector);

    unitVector.x = t_vector.x / mag;
    unitVector.y = t_vector.y / mag;

    return unitVector;
}

void VectorMath::normalize(sf::Vector2f& t_vector)
{
    float mag = magnitude(t_vector);

    t_vector.x = t_vector.x / mag;
    t_vector.y = t_vector.y / mag;
}

sf::Vector2f VectorMath::scale(sf::Vector2f t_vector, float t_scaler)
{
    sf::Vector2f newVector;

    newVector.x = t_vector.x * t_scaler;
    newVector.y = t_vector.y * t_scaler;

    return newVector;
}

sf::Vector2f VectorMath::divide(sf::Vector2f t_vector, float t_diviser)
{
    sf::Vector2f newVector;

    newVector.x = t_vector.x * t_diviser;
    newVector.y = t_vector.y * t_diviser;

    return newVector;
}