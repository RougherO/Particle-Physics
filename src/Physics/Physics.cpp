#include "Physics.hpp"
#include <cmath>
#include <cstdlib>
#include <numbers>

void Physics::setMaxLength(float maxLength)
{
    Transform::setPixelToWorldRatio(maxLength);
}

void Physics::createBoundary(float x, float y, float length, float height)
{
    originX = x + 1;
    originY = y + 1;
    boundLength = length - 1;
    boundHeight = height - 1;

    b2BodyDef boundDef;
    auto [worldX, worldY] = Transform::pixelToWorld({ x, y });
    auto [worldLength, worldHeight] = Transform::pixelToWorld({ length, height });
    boundDef.position.Set(worldX, worldY);
    boundDef.type = b2_staticBody;
    boundDef.allowSleep = false; // since boundary will have continuous collision

    b2ChainShape boundShape;
    b2Vec2 vertices[4];
    vertices[0] = { worldX, worldY };
    vertices[1] = { worldX, worldY + worldHeight };
    vertices[2] = { worldX + worldLength, worldY + worldHeight };
    vertices[3] = { worldX + worldLength, worldY };
    boundShape.CreateLoop(vertices, 4);

    b2FixtureDef boundfixtureDef;
    // Doesn't impact dynamic bodies
    // boundfixtureDef.density = 1.f;
    // boundfixtureDef.friction = 1.f;
    // boundfixtureDef.restitution = 0.f;
    boundfixtureDef.shape = &boundShape;

    b2Body* boundary = boundaryBody = m_world.CreateBody(&boundDef);
    boundary->CreateFixture(&boundfixtureDef);
}

void Physics::spawnCircle()
{
    auto [x, y] = m_shooter.position;
    b2BodyDef circleDef;
    circleDef.type = b2_dynamicBody;
    auto [worldX, worldY] = Transform::pixelToWorld(x, y);
    circleDef.position.Set(worldX, worldY);
    circleDef.fixedRotation = false;
    circleDef.allowSleep = true;
    circleDef.angle = angleOfEject;
    float worldVel = Transform::pixelToWorld(velOfEject);
    circleDef.linearVelocity = { worldVel * std::cos(angleOfEject), -worldVel * std::sin(angleOfEject) };

    b2CircleShape circleShape;
    if (randomRadius) {
        radius = randomRadiusllimit + (rand() % 101) / 100.f * (randomRadiusulimit - randomRadiusllimit);
    }
    float worldRadius = Transform::pixelToWorld(radius);
    circleShape.m_radius = worldRadius;

    b2FixtureDef circleFixtureDef;
    circleFixtureDef.density = density;
    circleFixtureDef.friction = friction;
    circleFixtureDef.restitution = coeffOfRest;
    circleFixtureDef.shape = &circleShape;

    b2Body* circle = m_world.CreateBody(&circleDef);
    circle->CreateFixture(&circleFixtureDef);

    auto [iter, _] = m_circleList.emplace(circle, radius);
    iter->second.setOrigin(radius, radius);
    iter->second.setPosition(x, y);

    sf::Color color {};
    if (circleColorRandom) {
        color = sf::Color {
            rand() % 256,
            rand() % 256,
            rand() % 256,
            255
        };
    } else {
        color = sf::Color {
            circleColor[0] * 255,
            circleColor[1] * 255,
            circleColor[2] * 255,
            circleColor[3] * 255
        };
    }
    iter->second.setFillColor(color);
}

void Physics::update(float dt)
{
    m_world.Step(dt, m_velIterations, m_posIterations);
    // Will implement dynamic boundaries later
    // m_boundary[0].position = { originX, originY };
    // m_boundary[1].position = { originX, originY + boundHeight };
    // m_boundary[2].position = { originX + boundLength, originY + boundHeight };
    // m_boundary[3].position = { originX + boundLength, originY };
    // m_boundary[4].position = m_boundary[0].position;
}

void Physics::updateShooterPos(const sf::Vector2f& pos)
{
    m_shooter.setPosition(pos);
    m_shooter.setAngleinRadians(angleOfEject);
}

void Physics::draw(sf::RenderWindow& window)
{
    for (b2Body* obj { m_world.GetBodyList() }; obj; obj = obj->GetNext()) {
        sf::CircleShape& circle = m_circleList[obj];
        circle.setPosition(Transform::worldToPixel(obj->GetPosition()));
        window.draw(circle);
    }
    window.draw(m_boundary);
    window.draw(m_shooter);
}
