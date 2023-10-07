#include "Shooter.hpp"

Shooter::Shooter()
{
    wheel1.setOrigin(wheel1.getRadius(), wheel1.getRadius());
    wheel2.setOrigin(wheel2.getRadius(), wheel2.getRadius());
    wheel1.setPosition(0, wheelDist);
    wheel2.setPosition(0, -wheelDist);

    cannon.setOrigin(0, cannon.getSize().y / 2);
    cannon.setPosition(0, 0);
}

Shooter::Shooter(float x, float y)
    : position { x, y }
{
    wheel1.setOrigin(wheel1.getRadius(), wheel1.getRadius());
    wheel2.setOrigin(wheel2.getRadius(), wheel2.getRadius());
    wheel1.setPosition(x, y + wheelDist);
    wheel2.setPosition(x, y - wheelDist);

    cannon.setOrigin(0, cannon.getSize().y / 2);
    cannon.setPosition(x, y);
}

Shooter::Shooter(const sf::Vector2f& pos)
    : position { pos }
{
    auto [x, y] = pos;
    wheel1.setOrigin(wheel1.getRadius(), wheel1.getRadius());
    wheel2.setOrigin(wheel2.getRadius(), wheel2.getRadius());
    wheel1.setPosition(x, y + wheelDist);
    wheel2.setPosition(x, y - wheelDist);

    cannon.setOrigin(0, cannon.getSize().y / 2);
    cannon.setPosition(x, y);
}

void Shooter::setAngleinRadians(float angle)
{
    wheel1.setPosition(position.x + std::sin(angle) * wheelDist, position.y + std::cos(angle) * wheelDist);
    wheel2.setPosition(position.x - std::sin(angle) * wheelDist, position.y - std::cos(angle) * wheelDist);
    angle = -angle * 180 * std::numbers::inv_pi;
    cannon.setRotation(angle);
}

void Shooter::setAngleinRadians(float x, float y)
{
    float angle = std::atan((y - position.y) / (x - position.x));
    setAngleinRadians(angle);
}

void Shooter::setPosition(float x, float y)
{
    position = { x, y };
    cannon.setPosition(x, y);
    float angle = -cannon.getRotation() * std::numbers::pi / 180;
    wheel1.setPosition(position.x + std::sin(angle) * wheelDist, position.y + std::cos(angle) * wheelDist);
    wheel2.setPosition(position.x - std::sin(angle) * wheelDist, position.y - std::cos(angle) * wheelDist);
}

void Shooter::setPosition(const sf::Vector2f& pos)
{
    position = pos;
    setPosition(pos.x, pos.y);
}

void Shooter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(wheel1);
    target.draw(wheel2);
    target.draw(cannon);
}