#pragma once
#include "SFML/Graphics.hpp"
#include "../map/Map.h"

class Entity
{
public:
	virtual ~Entity() = default;
	virtual void update(float dt, const sf::Vector2f& mousePosition, const Map& map) = 0;
	virtual void render(sf::RenderWindow& w) = 0;

	sf::Vector2f getPosition() const { return m_position; }
	void setPosition(const sf::Vector2f& position) { m_position = position; }
protected:
	sf::Vector2f m_position;
};

