#include "MenuScene.h"
#include <iostream>

MenuScene::MenuScene(const sf::RenderWindow& w) 
	: m_window(w)
	, m_startBtn("START", sf::Vector2f({ 200, 60 }))
	, m_settingsBtn("SETTINGS", sf::Vector2f({ 200, 60 }))
	, m_exitBtn("EXIT", sf::Vector2f({ 200, 60 }))
{
	centerButtons();
}

void MenuScene::handleEvent(const sf::Event& event)
{
	if (const auto* resized = event.getIf<sf::Event::Resized>()) { centerButtons(); }
	m_startBtn.handleEvent(event, m_window);
	m_settingsBtn.handleEvent(event, m_window);
	m_exitBtn.handleEvent(event, m_window);
}

void MenuScene::onStart(std::function<void()> callback)
{
	m_startBtn.setOnClick(std::move(callback));
}

void MenuScene::onSettings(std::function<void()> callback)
{
	m_settingsBtn.setOnClick(std::move(callback));
}

void MenuScene::onExit(std::function<void()> callback)
{
	m_exitBtn.setOnClick(std::move(callback));
}

void MenuScene::render(sf::RenderWindow& w)
{
	m_startBtn.render(w);
	m_settingsBtn.render(w);
	m_exitBtn.render(w);
}

void MenuScene::centerButtons()
{
	auto size = m_window.getSize();
	sf::Vector2f center = { size.x / 2.f, size.y / 2.f };

	std::array<Button*, 3> buttons = { &m_startBtn, &m_settingsBtn, &m_exitBtn };
	for (int i = 0; i < 3; ++i) {
		float offsetY = (i - 1) * MARGIN;
		buttons[i]->setPosition({ center.x, center.y + offsetY });
	}
}
