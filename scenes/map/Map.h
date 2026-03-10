#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

constexpr int TILE_SIZE = 32;
constexpr int MAP_WIDTH = 400;
constexpr int MAP_HEIGHT = 400;

enum TileType {
	GRASS,
	WATER,
	WALL
};

class Map
{
public:
	Map();

	bool isSolid(float x, float y) const;
	bool canMove(const sf::Vector2f& pos, float radius) const;
	void render(sf::RenderWindow& w, const sf::Vector2f& leftBorder);
private:
	void generate();

	std::vector<std::vector<TileType>> m_tiles;
};

