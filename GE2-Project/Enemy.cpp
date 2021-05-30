#include "Enemy.h"

int Enemy::s_nextID = 0;

Enemy::Enemy(Tile* t_startTile, float t_bodySize)
{
    m_currentTile = t_startTile;
    m_currentTile->setIsOccupied(true);
    m_id = s_nextID++;

    m_body.setFillColor(sf::Color::Red);
    m_body.setSize(sf::Vector2f(t_bodySize, t_bodySize));
    m_body.setPosition(m_currentTile->getPosition());
}

void Enemy::setPath(std::vector<Tile*> t_path)
{
    m_path = t_path;
}

void Enemy::update(float t_dt)
{
    m_movemnetDelay -= t_dt;

    if (m_path.size() != 0)
    {
        if (m_movemnetDelay <= 0.0f)
        {
            if (!m_path[m_path.size() - 1]->getIsOccupied())
            {
                //We free our current tile, move onto the next one and reduce the path.
                m_currentTile->setIsOccupied(false);
                m_currentTile = m_path[m_path.size() - 1];
                m_currentTile->setIsOccupied(true);
                m_body.setPosition(m_currentTile->getPosition());
                m_path.pop_back();
                m_movemnetDelay = m_MAX_MOVEMENT_DELAY;

                //If we have reached the end of the path we need to die
                //and free our tile.
                if (m_path.size() == 0)
                {
                    m_killMe = true;
                    m_currentTile->setIsOccupied(false);
                }
            }
        }
    }
}

void Enemy::render(sf::RenderWindow& t_window)
{
    t_window.draw(m_body);
}

int Enemy::getID()
{
    return m_id;
}

bool Enemy::getKillMe()
{
    return m_killMe;
}

Tile* Enemy::getCurrentTile()
{
    return m_currentTile;
}
