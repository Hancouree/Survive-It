#include "GameScene.h"

GameScene::GameScene(const sf::RenderWindow& w, NetworkManager& m) 
	: m_window(w)
	, m_networkManager(m)
{
	auto size = w.getSize();
	m_camera.setSize({ float(size.x), float(size.y) });

	m_networkManager.onConnected([this](std::string uid) { m_localUid = uid; });
}

void GameScene::update(float dt)
{
	if (auto state = m_networkManager.pollState(); !state.empty()) {
		parseState(state);
	}

	auto mouseScreen = sf::Mouse::getPosition(m_window);
	sf::Vector2f mouseWorld = m_window.mapPixelToCoords(mouseScreen, m_camera);

	InputPacket packet;
	packet.type = PACKET_INPUT;
	packet.moveDir = 0x00;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) packet.moveDir = 0x01;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) packet.moveDir = 0x04;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) packet.moveDir = 0x02;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) packet.moveDir = 0x08;

	packet.shooting = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);

	m_player.update(dt, mouseWorld, m_map);

	packet.aimAngle = m_player.angle();
	
	m_networkManager.sendInput(packet);
}

void GameScene::handleEvent(const sf::Event& e)
{
	if (const auto* resized = e.getIf<sf::Event::Resized>()) {
		m_camera.setSize({ float(resized->size.x), float(resized->size.y) });
	}
}

void GameScene::render(sf::RenderWindow& w)
{
	auto pos = m_player.getPosition();
	auto halfSize = m_camera.getSize() / 2.f;

	int mapWidth = MAP_WIDTH * TILE_SIZE;
	int mapHeight = MAP_HEIGHT * TILE_SIZE;

	float cx = std::clamp(pos.x, halfSize.x, mapWidth - halfSize.x);
	float cy = std::clamp(pos.y, halfSize.y, mapHeight - halfSize.y);

	m_camera.setCenter({ cx, cy });
	w.setView(m_camera);
	m_map.render(w, m_camera.getCenter() - halfSize);
	m_player.render(w);
	w.setView(w.getDefaultView());
}

void GameScene::parseState(const std::vector<uint8_t>& data)
{
	if (data.size() < 2) return;

	size_t offset = 1;
	uint8_t playerCount = data[offset++];

	for (int i = 0; i < playerCount; ++i) {
		if (offset >= data.size()) break;
		uint8_t uidLen = data[offset++];
		if (offset + uidLen > data.size()) break;
		std::string uid(data.begin() + offset, data.begin() + offset + uidLen);
		offset += uidLen;

		if (offset + 4 * 4 + 1 > data.size()) break;
		float x, y, aimAngle, hp;
		memcpy(&x, data.data() + offset, 4); offset += 4;
		memcpy(&y, data.data() + offset, 4); offset += 4;
		memcpy(&aimAngle, data.data() + offset, 4); offset += 4;
		memcpy(&hp, data.data() + offset, 4); offset += 4;
		bool alive = data[offset++];

		if (uid == m_localUid) {
			m_player.setPosition({ x, y });
			m_player.setHp(hp);
		}
		else {
			auto& p = m_remotePlayers[uid];
			p.setPosition({ x, y });
			p.setAngle(aimAngle);
			p.setHp(hp);
		}
	}

	// удаляем игроков которых нет в пакете
	// (они отключились или умерли)
	// собираем uid из пакета
}
