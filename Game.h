#pragma once
#include <iostream>
#include "network/NetworkManager.h"
#include "FSM.h"
#include "scenes/ConnectingScene.h"
#include "scenes/MenuScene.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int MOVE_SPEED = 40;

class Game
{
public:
	Game();

	void run();
private:
	void initWindow(unsigned int width, unsigned int height);
	void initScenes();

	sf::RenderWindow* window;
	NetworkManager m_networkManager;
	FSM m_stateMachine;
	std::unordered_map<FSM::States, Scene*> m_scenes;
};

