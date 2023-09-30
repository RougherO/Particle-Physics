#pragma once
#include <SFML/Graphics.hpp>

struct Particles : sf::CircleShape {
    Particles();
    Particles(float radius, float mass = 10.f);

    // overriding default setPosition
    void setPosition(const sf::Vector2f& pos);

    float mass {};
    sf::Vector2f Pos {};
    sf::Vector2f prevVel {};
    sf::Vector2f Vel {};
    sf::Vector2f Acc {};
};