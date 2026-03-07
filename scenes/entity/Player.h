#pragma once
#include "LivingEntity.h"

constexpr float MOVE_SPEED = 300.f;

class Player : public LivingEntity
{
public:
	Player();

	float angle() const { return m_angle; }

	void update(float dt, const sf::Vector2f& mousePosition, const Map& map) override;
	void render(sf::RenderWindow& w) override;
private:
	sf::CircleShape m_texture;
	float m_radius;
	float m_angle;
};

