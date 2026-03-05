#include "ConnectingScene.h"
#include <cmath>

ConnectingScene::ConnectingScene()
{
    m_text = new sf::Text(FontManager::getFont("fonts/Roboto-Black.ttf"));
    m_text->setString("Connecting");
    m_text->setCharacterSize(25);
    m_text->setFillColor(sf::Color::White);
    m_text->setLetterSpacing(1);
    
    auto bounds = m_text->getLocalBounds();
    m_text->setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });

    m_arc.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
    m_arc.resize((ARC_POINTS + 1) * 2);
}

ConnectingScene::~ConnectingScene()
{
    if (m_text) delete m_text;
}

void ConnectingScene::updateArc(sf::Vector2f center)
{
    for (int i = 0; i <= ARC_POINTS; ++i) {
        float angle = sf::degrees(m_angle + (ARC_LENGTH / ARC_POINTS) * i).asRadians();
        float outer = CIRCLE_RADIUS + CIRCLE_THICKNESS;
        float inner = CIRCLE_RADIUS;

        float cosA = std::cos(angle);
        float sinA = std::sin(angle);

        uint8_t alpha = static_cast<uint8_t>(255.f * i / ARC_POINTS);

        m_arc[i * 2] = { { center.x + cosA * outer, center.y + sinA * outer }, sf::Color(255, 255, 255, alpha) };
        m_arc[i * 2 + 1] = { { center.x + cosA * inner, center.y + sinA * inner }, sf::Color(255, 255, 255, alpha) };
    }
}

void ConnectingScene::update(float dt)
{
    m_angle += ROTATION_SPEED * dt;
    if (m_angle >= 360.f) m_angle -= 360.f;
}

void ConnectingScene::render(sf::RenderWindow& window)
{
    auto size = window.getSize();
    sf::Vector2f center = { size.x / 2.f, size.y / 2.f };
    updateArc(center);

    m_text->setPosition({ center.x, center.y - CIRCLE_RADIUS - 25.f });

    window.draw(m_arc);
    window.draw(*m_text);
}