#include "Button.h"
#include "../fonts/FontManager.h"

Button::Button(const std::string& text, const sf::Vector2f& size) 
	: m_normalColor(sf::Color(70, 70, 70))
	, m_hoverColor(sf::Color(100, 100, 100))
	, m_clickColor(sf::Color(50, 50, 50))
{
	m_rect.setSize(size);
	m_rect.setOrigin({ size.x / 2, size.y / 2 });

	m_text = sf::Text(FontManager::getFont("fonts/Roboto-Black.ttf"));
	m_text->setCharacterSize(20);
	m_text->setLetterSpacing(1);
	m_text->setFillColor(sf::Color::Black);
	m_text->setString(text);

	auto bounds = m_text->getLocalBounds();
	m_text->setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });
}

void Button::setPosition(const sf::Vector2f& position)
{
	m_rect.setPosition(position);
	m_text->setPosition(position);
}

bool Button::isHovered(const sf::RenderWindow& w) const
{
	auto mouse = sf::Mouse::getPosition(w);
	return m_rect.getGlobalBounds().contains({ float(mouse.x), float(mouse.y) });
}


void Button::handleEvent(const sf::Event& e, const sf::RenderWindow& w)
{
	if (isHovered(w)) {
		m_rect.setFillColor(m_hoverColor);

		if (auto* mousePressed = e.getIf<sf::Event::MouseButtonPressed>()) {
			if (mousePressed->button == sf::Mouse::Button::Left) {
				m_rect.setFillColor(m_clickColor);
				if (m_onClick) m_onClick();
			}
		}
	}
	else {
		m_rect.setFillColor(m_normalColor);
	}
}

void Button::setOnClick(std::function<void()> callback)
{
	m_onClick = std::move(callback);
}

void Button::render(sf::RenderWindow& w)
{
	w.draw(m_rect);
	w.draw(*m_text);
}

