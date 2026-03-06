#include "Map.h"
#include <iostream>

Map::Map()
{
	generate();
}

bool Map::isSolid(float x, float y) const
{
    int tileX = x / TILE_SIZE, tileY = y / TILE_SIZE;
    if (tileX < 0 || tileY < 0 || tileX >= MAP_WIDTH || tileY >= MAP_HEIGHT) return true;
    return m_tiles[tileY][tileX] == TileType::WALL;
}

bool Map::canMove(const sf::Vector2f& pos, float radius) const {
    return !isSolid(pos.x - radius, pos.y - radius) &&
        !isSolid(pos.x + radius, pos.y - radius) &&
        !isSolid(pos.x - radius, pos.y + radius) &&
        !isSolid(pos.x + radius, pos.y + radius);
}

void Map::render(sf::RenderWindow& w, const sf::Vector2f& leftBorder)
{
	sf::RectangleShape tile({ TILE_SIZE, TILE_SIZE });
	auto size = w.getSize();
	int startX = std::max(0, int(leftBorder.x / TILE_SIZE)), startY = std::max(0, int(leftBorder.y / TILE_SIZE));
	int endX = std::min(MAP_WIDTH, startX + int(size.x / TILE_SIZE) + 2), endY = std::min(MAP_HEIGHT, startY + int(size.y / TILE_SIZE) + 2);
	for (int y = startY; y < endY; ++y) {
		for (int x = startX; x < endX; ++x) {
			switch (m_tiles[y][x])
			{
			case TileType::GRASS: tile.setFillColor(sf::Color(100, 180, 100)); break;
			case TileType::WATER: tile.setFillColor(sf::Color(50, 100, 200)); break;
			case TileType::WALL: tile.setFillColor(sf::Color(80, 80, 80)); break;
			}

			tile.setPosition({ float(x * TILE_SIZE), float(y * TILE_SIZE) });
			w.draw(tile);
		}
	}
}

void Map::generate()
{
    m_tiles.resize(MAP_HEIGHT, std::vector<TileType>(MAP_WIDTH));

    // заполняем травой
    for (int y = 0; y < MAP_HEIGHT; ++y)
        for (int x = 0; x < MAP_WIDTH; ++x)
            m_tiles[y][x] = TileType::GRASS;

    // несколько препятствий внутри
    for (int x = 10; x < 15; ++x) m_tiles[10][x] = TileType::WALL;
    for (int x = 20; x < 25; ++x) m_tiles[20][x] = TileType::WALL;
    for (int y = 5; y < 15; ++y) m_tiles[y][30] = TileType::WALL;
    for (int y = 25; y < 35; ++y) m_tiles[y][15] = TileType::WALL;

    // водоем
    for (int y = 30; y < 35; ++y)
        for (int x = 35; x < 42; ++x)
            m_tiles[y][x] = TileType::WATER;
}
