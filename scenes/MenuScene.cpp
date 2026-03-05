#include "MenuScene.h"
#include <iostream>

MenuScene::MenuScene(const sf::RenderWindow& w) : m_window(w) {
	m_startBtn = std::make_unique<Button>("START", sf::Vector2f({ 200, 60 }));
	m_startBtn->setOnClick([this]() { std::cout << "START CLICKED\n"; });

	m_settingsBtn = std::make_unique<Button>("SETTINGS", sf::Vector2f({ 200, 60 }));
	m_settingsBtn->setOnClick([this]() { std::cout << "SETTINGS CLICKED\n"; });

	m_exitBtn = std::make_unique<Button>("EXIT", sf::Vector2f({ 200, 60 }));
	m_exitBtn->setOnClick([this]() { std::cout << "EXIT CLICKED\n"; });
}

void MenuScene::handleEvent(const sf::Event& event)
{
	m_startBtn->handleEvent(event, m_window);
	m_settingsBtn->handleEvent(event, m_window);
	m_exitBtn->handleEvent(event, m_window);
}

void MenuScene::render(sf::RenderWindow& w)
{
	auto size = w.getSize();
	sf::Vector2f center = { size.x / 2.f, size.y / 2.f };

	std::array<Button*, 3> buttons = { m_startBtn.get(), m_settingsBtn.get(), m_exitBtn.get() };
	int count = buttons.size();

	for (int i = 0; i < count; ++i) {
		float offsetY = (i - (count - 1) / 2.f) * MARGIN;
		buttons[i]->setPosition({ center.x, center.y + offsetY });
		buttons[i]->render(w);
	}
}
