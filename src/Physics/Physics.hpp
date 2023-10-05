#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <unordered_map>
#include "../Transform/Transform.hpp"
#include "../Shooter/Shooter.hpp"

struct Physics {
    inline static float coeffOfRest { 0.5f };
    inline static float friction { 0.f };
    inline static float density { 10.f };
    // inline static float lengthOfBox { 10.f };
    // inline static float heightOfBox { 10.f };

    // Boundary Properties
    inline static float originX {};
    inline static float originY {};
    inline static float boundLength {};
    inline static float boundHeight {};
    inline static b2Body* boundaryBody {};
    // Boundary internal properties
    inline static sf::VertexArray m_boundary { sf::PrimitiveType::LineStrip, 5 };

    // Circle properties
    inline static bool randomRadius {};
    inline static float randomRadiusllimit { 5.f };
    inline static float randomRadiusulimit { 50.f };
    inline static float radius { 10.f };
    inline static bool circleColorRandom {};
    inline static float circleColor[4] { 1.f, 1.f, 1.f, 1.f };
    inline static std::unordered_map<b2Body*, sf::CircleShape> m_circleList {};

    // Shooter properties
    inline static float angleOfEject {};
    inline static float velOfEject { 1000.f };
    // Shooter internal properties
    inline static Shooter m_shooter;

    static void setMaxLength(float maxLength);

    static void createBoundary(float x, float y, float length, float height);
    static void spawnCircle();

    static void updateShooterPos(const sf::Vector2f& pos);
    static void update(float dt);
    static void draw(sf::RenderWindow& window);

    inline static size_t m_velIterations { 6 };
    inline static size_t m_posIterations { 2 };

    // Game World
    inline static b2Vec2 m_gravity { 0.f, 10.f };
    inline static b2World m_world { m_gravity };
};