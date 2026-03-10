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
    m_tiles.resize(MAP_HEIGHT, std::vector<TileType>(MAP_WIDTH, TileType::GRASS));

    for (int x = 0; x < MAP_WIDTH; x++) {
        m_tiles[0][x] = TileType::WALL;
        m_tiles[MAP_HEIGHT - 1][x] = TileType::WALL;
    }
    for (int y = 0; y < MAP_HEIGHT; y++) {
        m_tiles[y][0] = TileType::WALL;
        m_tiles[y][MAP_WIDTH - 1] = TileType::WALL;
    }
     
    struct Lake { int cx, cy, rx, ry; };
    std::vector<Lake> lakes = {
        { 40,  35, 12, 8  },
        { 160, 50, 10, 14 },
        { 80,  150, 15, 10 },
        { 150, 160, 8,  12 },
        { 100, 90,  6,  6  },
    };
    for (auto& lake : lakes) {
        for (int y = lake.cy - lake.ry; y <= lake.cy + lake.ry; y++) {
            for (int x = lake.cx - lake.rx; x <= lake.cx + lake.rx; x++) {
                if (x <= 0 || x >= MAP_WIDTH - 1 || y <= 0 || y >= MAP_HEIGHT - 1) continue;
                float dx = float(x - lake.cx) / lake.rx;
                float dy = float(y - lake.cy) / lake.ry;
                if (dx * dx + dy * dy <= 1.0f)
                    m_tiles[y][x] = TileType::WATER;
            }
        }
    }

    struct House { int x, y, w, h; };
    std::vector<House> houses = {
        { 20,  20,  6, 5 },
        { 30,  70,  8, 6 },
        { 70,  20,  5, 5 },
        { 120, 20,  7, 5 },
        { 160, 30,  6, 6 },
        { 20,  120, 8, 5 },
        { 60,  110, 5, 7 },
        { 100, 130, 6, 6 },
        { 140, 110, 7, 5 },
        { 170, 140, 5, 5 },
        { 30,  170, 6, 6 },
        { 80,  170, 8, 5 },
        { 130, 170, 5, 7 },
        { 170, 170, 6, 5 },
        { 90,  60,  5, 5 },
        { 110, 100, 6, 4 },
    };
    for (auto& h : houses) {
        for (int y = h.y; y < h.y + h.h; y++) {
            for (int x = h.x; x < h.x + h.w; x++) {
                if (x <= 0 || x >= MAP_WIDTH - 1 || y <= 0 || y >= MAP_HEIGHT - 1) continue;
                bool isPerimeter = (x == h.x || x == h.x + h.w - 1 ||
                    y == h.y || y == h.y + h.h - 1);
                if (isPerimeter) m_tiles[y][x] = TileType::WALL;
            }
        }
        int doorX = h.x + h.w / 2;
        int doorY = h.y + h.h - 1;
        if (doorX > 0 && doorX < MAP_WIDTH - 1 && doorY > 0 && doorY < MAP_HEIGHT - 1)
            m_tiles[doorY][doorX] = TileType::GRASS;
    }
}