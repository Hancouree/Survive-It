#pragma once
#include "Scene.h"
#include "map/Map.h"
#include "entity/Player.h"

class GameScene : public Scene
{
public:
	GameScene(const sf::RenderWindow& w);
	void update(float dt);
	void handleEvent(const sf::Event& e);
	void render(sf::RenderWindow& w);
private:
	const sf::RenderWindow& m_window;
	Map m_map;
	Player m_player;
	sf::View m_camera;
};

