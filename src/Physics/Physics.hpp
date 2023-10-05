#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <unordered_map>
#include "../Transform/Transform.hpp"

struct Physics {
    inline static float coeffOfRest { 1.f };
    inline static float friction { 0.f };
    inline static float density { 10.f };
    inline static float lengthOfBox { 10.f };
    inline static float heightOfBox { 10.f };

    // Circle properties
    inline static float radius { 10.f };
    inline static std::unordered_map<b2Body*, sf::CircleShape> circleList {};

    static void setMaxLength(float length);

    // static void createBoundary(float length, float height)
    // {
    //     b2BodyDef bodyDef;
    //     bodyDef.position.Set(0.f, 0.f);
    //     bodyDef.type = b2_staticBody;
    //     bodyDef.allowSleep = false; // since boundary will have continuous collision

    //     b2ChainShape boundShape;
    //     b2Vec2 vertices[4];
    //     vertices[0] = { 0.f, 0.f };
    //     vertices[1] = { 0.f, height };
    //     vertices[2] = { length, height };
    //     vertices[3] = { length, 0.f };
    //     boundShape.CreateLoop(vertices, 4);

    //     b2FixtureDef fixtureDef;
    //     fixtureDef.density = 1.f;
    //     fixtureDef.friction = 0.f;
    //     fixtureDef.restitution = 1.f;
    //     fixtureDef.shape = &boundShape;
    // }

    static void spawnCircle(float x, float y);
    static void update(float dt);
    static void draw(sf::RenderWindow& window);

private:
    inline static size_t m_velIterations { 6 };
    inline static size_t m_posIterations { 2 };

    inline static b2Vec2 m_gravity { 0.f, 1.5f };
    inline static b2World m_world { m_gravity };
};