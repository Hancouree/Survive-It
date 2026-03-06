#include "Player.h"

Player::Player() 
	: m_radius(22.f)
	, m_angle(0.f)
{
	m_texture.setRadius(m_radius);
	m_texture.setFillColor(sf::Color::White);
	m_texture.setOrigin({ m_radius, m_radius });
}

void Player::update(float dt, const sf::Vector2f& mousePosition, const Map& map)
{
	sf::Vector2f dir = mousePosition - m_position;
	m_angle = std::atan2(dir.y, dir.x);

	sf::Vector2f offset{ 0.f, 0.f };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) offset.y -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) offset.y += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) offset.x -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) offset.x += 1.f;

	float length = offset.length();
	if (length > 0.f) offset /= length;
	sf::Vector2f newPosition = m_texture.getPosition() + offset * MOVE_SPEED * dt;
	if (!map.canMove(newPosition, m_texture.getRadius())) return;

	float mapWidth = MAP_WIDTH * TILE_SIZE, mapHeight = MAP_HEIGHT * TILE_SIZE;

	m_position = {
		std::clamp(newPosition.x, m_radius, mapWidth - m_radius),
		std::clamp(newPosition.y, m_radius, mapHeight - m_radius)
	};
}

void Player::render(sf::RenderWindow& w)
{
	m_texture.setPosition(m_position);
	sf::Vertex line[] = { 
		{ m_position, sf::Color::Black },
		{ m_position + sf::Vector2f{ std::cos(m_angle), std::sin(m_angle) } * m_radius, sf::Color::Black }
	};
	w.draw(m_texture);
	w.draw(line, 2, sf::PrimitiveType::Lines);
}
