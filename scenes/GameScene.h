#pragma once
#include "Scene.h"
#include "map/Map.h"
#include "entity/Player.h"
#include "../network/NetworkManager.h"

class GameScene : public Scene
{
public:
	GameScene(const sf::RenderWindow& w, NetworkManager& m);

	void update(float dt);
	void handleEvent(const sf::Event& e);
	void render(sf::RenderWindow& w);
private:
	void parseState(const std::vector<uint8_t>& state);

	const sf::RenderWindow& m_window;
	NetworkManager& m_networkManager;

	Map m_map;
	Player m_player;
	std::string m_localUid;
	std::unordered_map<std::string, Player> m_remotePlayers;
	sf::View m_camera;
};