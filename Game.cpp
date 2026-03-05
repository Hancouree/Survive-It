#include "Game.h"

Game::Game()
{
	initWindow(WIDTH, HEIGHT);
	initScenes();
	
	m_networkManager.connect("127.0.0.1", 5050);
	m_networkManager.onConnected([this]() {
		std::cout << "CONNECTED\n";
	});
	
	run();
}

void Game::initWindow(unsigned int width, unsigned int height)
{
	window = new sf::RenderWindow(sf::VideoMode({ width, height }), "Survive It");
	window->setFramerateLimit(60);
}

void Game::initScenes()
{
	m_scenes[FSM::CONNECTING] = new ConnectingScene;
}

void Game::run()
{
	sf::Clock clock;
	while (window->isOpen()) {
		float dt = clock.restart().asSeconds();

		while (auto event = window->pollEvent()) {
			if (event->is<sf::Event::Closed>()) window->close();
		}

		Scene* currentScene = m_scenes[m_stateMachine.getState()];
		if (currentScene) currentScene->update(dt);

		window->clear(sf::Color(50, 50, 50));

		if (currentScene) currentScene->render(*window);

		window->display();
	}
}
