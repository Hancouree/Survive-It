#pragma once
#include "Scene.h"
#include "../fonts/FontManager.h"

constexpr float CIRCLE_RADIUS = 30.f;
constexpr float CIRCLE_THICKNESS = 4.f;
constexpr float ROTATION_SPEED = 300.f;
constexpr int ARC_POINTS = 60;
constexpr float ARC_LENGTH = 270.f;

class ConnectingScene : public Scene {
public:
    ConnectingScene();
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event) override {}
private:
    void updateArc(sf::Vector2f center);

    sf::VertexArray m_arc;
    float m_angle = 0.f;
    std::optional<sf::Text> m_text;
};