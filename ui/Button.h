#pragma once
#include "SFML/Graphics.hpp"
#include <functional>

class Button
{
public:
	Button(const std::string& text, const sf::Vector2f& size);

	void setPosition(const sf::Vector2f& position);
	void handleEvent(const sf::Event& e, const sf::RenderWindow& w);
	void setOnClick(std::function<void()> callback);
	void render(sf::RenderWindow& w);
private:
	bool isHovered(const sf::RenderWindow& w) const;

	sf::RectangleShape m_rect;
	std::optional<sf::Text> m_text;
	std::function<void()> m_onClick;
	sf::Color m_normalColor;
	sf::Color m_hoverColor;
	sf::Color m_clickColor;
};

