#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/b2_math.h>

class Transform {
    inline static float m_pixelToWorldRatio {};

public:
    // Provide maximum pixel length to automatically
    // set the world to pixel ratio
    static void setPixelToWorldRatio(float maxLength);
    static b2Vec2 pixelToWorld(const sf::Vector2f& pixelVec);
    static b2Vec2 pixelToWorld(float x, float y);
    static sf::Vector2f worldToPixel(const b2Vec2& worldVec);
    static sf::Vector2f worldToPixel(float x, float y);
    static float worldToPixel(float length);
    static float pixelToWorld(float length);
};