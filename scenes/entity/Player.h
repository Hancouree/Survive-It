#pragma once
#include "LivingEntity.h"

constexpr float MOVE_SPEED = 300.f;

class Player : public LivingEntity
{
public:
	Player();

	void setHp(float hp) { m_hp = hp; }
	void setAngle(float angle) { m_angle = angle; }
	float angle() const { return m_angle; }

	void update(float dt, const sf::Vector2f& mousePosition, const Map& map) override;
	void render(sf::RenderWindow& w) override;
private:
	sf::CircleShape m_texture;
	float m_radius;
	float m_angle;
};

