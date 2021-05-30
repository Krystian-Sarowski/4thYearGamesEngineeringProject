#include "Camera.h"

void Camera::setCameraPos()
{
	if (m_cameraPos.x - m_zoomLevel / 2 < 0)
	{
		m_cameraPos.x = m_zoomLevel / 2;
	}

	else if (m_cameraPos.x + m_zoomLevel / 2 > 3000)
	{
		m_cameraPos.x = 3000 - m_zoomLevel / 2;
	}

	if (m_cameraPos.y - m_zoomLevel / 2 < 0)
	{
		m_cameraPos.y = m_zoomLevel / 2;
	}

	else if (m_cameraPos.y + m_zoomLevel / 2 > 3000)
	{
		m_cameraPos.y = 3000 - m_zoomLevel / 2;
	}

	m_cameraView.setCenter(m_cameraPos);
}

Camera::Camera(sf::RenderWindow& t_window) :
	m_window(t_window),
	m_zoomLevel(3000),
	m_cameraPos(sf::Vector2f(1500.0f, 1500.0f))
{
	m_cameraView.setSize(sf::Vector2f(m_zoomLevel, m_zoomLevel));
	m_cameraView.setCenter(m_cameraPos);
	m_window.setView(m_cameraView);
}

void Camera::moveCamera(sf::Vector2f t_mousePosition)
{
	sf::Vector2f dir = t_mousePosition - m_cameraPos;

	float mag = VectorMath::magnitude(dir);
	mag = mag / 10.0f;

	dir = VectorMath::scale(VectorMath::unit(dir), mag);

	m_cameraPos += dir;

	setCameraPos();
	m_window.setView(m_cameraView);
}

void Camera::adjustZoom(float t_zoomAmount)
{
	m_zoomLevel -= (t_zoomAmount / 6.0f);

	if (m_zoomLevel < 30.0f)
	{
		m_zoomLevel = 30.0f;
	}
	else if (m_zoomLevel > 3000.0f)
	{
		m_zoomLevel = 3000.0f;
	}

	m_cameraView.setSize(sf::Vector2f(m_zoomLevel, m_zoomLevel));
	setCameraPos();
	m_window.setView(m_cameraView);
}
