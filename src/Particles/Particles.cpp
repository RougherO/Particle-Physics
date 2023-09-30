#include "Particles.hpp"

Particles::Particles()
    : CircleShape()
{
    setOrigin(getRadius(), getRadius());
}

Particles::Particles(float radius, float mass)
    : CircleShape(radius)
    , mass { mass }
{
    setOrigin(radius, radius);
}

void Particles::setPosition(const sf::Vector2f& pos)
{
    Pos = pos;
    CircleShape::setPosition(pos);
}