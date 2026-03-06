#pragma once
#include "Scene.h"
#include "../ui/Button.h"

constexpr int MARGIN = 80.f;

class MenuScene : public Scene
{
public:
	MenuScene(const sf::RenderWindow& w);

	void update(float dt) override {};
	void handleEvent(const sf::Event& event) override;
	void onStart(std::function<void()> callback);
	void onSettings(std::function<void()> callback);
	void onExit(std::function<void()> callback);
	void render(sf::RenderWindow& w) override;
private:
	void centerButtons();

	const sf::RenderWindow& m_window;
	Button m_startBtn, m_settingsBtn, m_exitBtn;
};

