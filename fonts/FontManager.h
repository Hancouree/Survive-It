#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class FontManager
{
public:
	FontManager() = delete;

	static sf::Font& getFont(const std::string& path) {
		if (!m_fonts.contains(path)) load(path);
		return m_fonts[path];
	}
private:
	static void load(const std::string& path) {
		sf::Font font;
		if (!font.openFromFile(path)) { throw std::runtime_error("Failed to load font: " + path); }
		m_fonts[path] = std::move(font);
	}

	static std::unordered_map<std::string, sf::Font> m_fonts;
};

