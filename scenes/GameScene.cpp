#include "GameScene.h"

GameScene::GameScene(const sf::RenderWindow& w) : m_window(w)
{
	auto size = w.getSize();
	m_camera.setSize({ float(size.x), float(size.y) });
}

void GameScene::update(float dt)
{
	auto mouseScreen = sf::Mouse::getPosition(m_window);
	sf::Vector2f mouseWorld = m_window.mapPixelToCoords(mouseScreen, m_camera);
	m_player.update(dt, mouseWorld, m_map);
}

void GameScene::handleEvent(const sf::Event& e)
{

}

void GameScene::render(sf::RenderWindow& w)
{
	auto pos = m_player.getPosition();
	auto halfSize = m_camera.getSize() / 2.f;

	float mapWidth = MAP_WIDTH * TILE_SIZE;
	float mapHeight = MAP_HEIGHT * TILE_SIZE;

	float cx = std::clamp(pos.x, halfSize.x, mapWidth - halfSize.x);
	float cy = std::clamp(pos.y, halfSize.y, mapHeight - halfSize.y);

	m_camera.setCenter({ cx, cy });
	w.setView(m_camera);
	m_map.render(w, m_camera.getCenter() - halfSize);
	m_player.render(w);
	w.setView(w.getDefaultView());
}
