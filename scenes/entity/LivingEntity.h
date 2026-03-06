#pragma once
#include "Entity.h"

class LivingEntity : public Entity 
{
public:
	LivingEntity() 
		: Entity()
		, m_hp(100)
		, m_maxHp(100)
	{}

	float hp() const { return m_hp; }
	bool alive() const { return m_hp > 0.f; }
	void takeDamage(float damage) { m_hp = std::max(0.f, m_hp - damage); }
private:
	float m_hp;
	float m_maxHp;
};

