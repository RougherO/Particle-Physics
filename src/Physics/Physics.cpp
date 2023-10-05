#include "Physics.hpp"

void Physics::setMaxLength(float length)
{
    Transform::setPixelToWorldRatio(length);
}

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

void Physics::spawnCircle(float x, float y)
{
    b2BodyDef circleDef;
    circleDef.type = b2_dynamicBody;
    auto [worldX, worldY] = Transform::pixelToWorld(x, y);
    circleDef.position.Set(worldX, worldY);
    circleDef.fixedRotation = false;
    circleDef.allowSleep = true;

    b2CircleShape circleShape;
    circleShape.m_radius = Transform::pixelToWorld(radius);

    b2FixtureDef circleFixtureDef;
    circleFixtureDef.density = density;
    circleFixtureDef.friction = friction;
    circleFixtureDef.restitution = coeffOfRest;
    circleFixtureDef.shape = &circleShape;

    b2Body* circle = m_world.CreateBody(&circleDef);
    circle->CreateFixture(&circleFixtureDef);

    auto [iter, _] = circleList.emplace(circle, radius);
    iter->second.setOrigin(radius, radius);
    iter->second.setPosition(x, y);
}

void Physics::update(float dt)
{
    m_world.Step(dt, m_velIterations, m_posIterations);
}

void Physics::draw(sf::RenderWindow& window)
{
    for (b2Body* obj { m_world.GetBodyList() }; obj; obj = obj->GetNext()) {
        sf::CircleShape& circle = circleList[obj];
        circle.setPosition(Transform::worldToPixel(obj->GetPosition()));
        window.draw(circle);
    }
}