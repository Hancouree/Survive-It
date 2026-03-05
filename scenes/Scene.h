#pragma once
#include <SFML/Graphics.hpp>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;
	virtual void handleEvent(const sf::Event& e) = 0;
	virtual void update(float dt) = 0;
	virtual void render(sf::RenderWindow& w) = 0;
};

