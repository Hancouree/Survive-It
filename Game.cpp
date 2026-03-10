#include "Game.h"

Game::Game()
{
	initWindow(WIDTH, HEIGHT);
	initScenes();

	m_networkManager.connect("127.0.0.1", 5050);
	m_networkManager.onConnected([this](std::string) { m_stateMachine.applyEvent(FSM::CONNECTED); });

	run();
}

void Game::initWindow(unsigned int width, unsigned int height)
{
	window = new sf::RenderWindow(sf::VideoMode({ width, height }), "Survive It");
	window->setFramerateLimit(0);
}

void Game::initScenes()
{
	m_scenes[FSM::CONNECTING] = new ConnectingScene;

	MenuScene* menuScene = new MenuScene(*window);
	menuScene->onStart([this]() { m_stateMachine.applyEvent(FSM::START_GAME); });
	menuScene->onSettings([this]() { std::cout << "Settings clicked\n"; });
	menuScene->onExit([this]() { window->close(); });
	m_scenes[FSM::MENU] = menuScene;
	
	m_scenes[FSM::IN_GAME] = new GameScene(*window, m_networkManager);
}

void Game::run()
{
	sf::Clock clock;
	while (window->isOpen()) {
		float dt = clock.restart().asSeconds();

		Scene* currentScene = m_scenes[m_stateMachine.getState()];
		while (auto event = window->pollEvent()) {
			if (event->is<sf::Event::Closed>()) window->close();
			if (const auto* resized = event->getIf<sf::Event::Resized>()) {
				sf::FloatRect visibleArea({ 0.f , 0.f }, {
					(float)resized->size.x,
					(float)resized->size.y
				});

				window->setView(sf::View(visibleArea)); 
			}

			if (currentScene) currentScene->handleEvent(*event);
		}

		if (currentScene) currentScene->update(dt);

		window->clear(sf::Color(50, 50, 50));

		if (currentScene) currentScene->render(*window);

		window->display();
	}
}
