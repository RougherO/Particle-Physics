#include "Transform.hpp"

// Provide maximum pixel length to automatically
// set the world to pixel ratio
void Transform::setPixelToWorldRatio(float maxLength)
{
    m_pixelToWorldRatio = maxLength / 50.f;
}

b2Vec2 Transform::pixelToWorld(const sf::Vector2f& pixelVec)
{
    return {
        pixelVec.x * 1 / m_pixelToWorldRatio,
        pixelVec.y * 1 / m_pixelToWorldRatio
    };
}

b2Vec2 Transform::pixelToWorld(float x, float y)
{
    return {
        x * 1 / m_pixelToWorldRatio,
        y * 1 / m_pixelToWorldRatio
    };
}

sf::Vector2f Transform::worldToPixel(const b2Vec2& worldVec)
{
    return {
        worldVec.x * m_pixelToWorldRatio,
        worldVec.y * m_pixelToWorldRatio
    };
}

sf::Vector2f Transform::worldToPixel(float x, float y)
{
    return {
        x * m_pixelToWorldRatio,
        y * m_pixelToWorldRatio
    };
}

float Transform::worldToPixel(float length)
{
    return length * m_pixelToWorldRatio;
}

float Transform::pixelToWorld(float length)
{
    return length * 1 / m_pixelToWorldRatio;
}
